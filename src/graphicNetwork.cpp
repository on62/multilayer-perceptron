#include "graphicNetwork.hpp"

#include <glibmm/main.h>
#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>
#include <cmath>
#include <vector>

GraphicNetwork::GraphicNetwork(const std::string &file, unsigned int timeout, const double &learningRate) : Network(file, learningRate)
{
	Glib::signal_timeout().connect(sigc::mem_fun(*this, &GraphicNetwork::on_redraw), timeout);

	size_t maxSize(0);
	for (const Vector &activation : activations)
	{
		size_t layerSize(activation.size() + 1);
		if (layerSize > maxSize)
			maxSize = layerSize;
	}

	size_t totalNumberOfLayers(numberOfNeuronLayers + 1);

	double ySpacing(0.8 / maxSize);
	double xSpacing(0.8 / numberOfNeuronLayers);
	double xStart(0.1);
	double middleY(0.5);

	if (xSpacing > ySpacing)
		nodeRadius = ySpacing * 0.25;
	else
		nodeRadius = xSpacing * 0.25;
	if (nodeRadius > 0.05)
		nodeRadius = 0.05;

	for (size_t l(0); l < totalNumberOfLayers; ++l)
	{
		size_t layerSize(activations[l].size());
		nodeCoordinates.push_back(std::vector<Coordinate>(layerSize));
		double x(xStart + l * xSpacing);
		for (size_t j(0); j < layerSize; ++j)
		{
			double y(middleY + (j - (layerSize - 1) * 0.5) * ySpacing);
			nodeCoordinates[l][j] = {x, y};
		}
		if (l < numberOfNeuronLayers)
		{
			nodeCoordinates[l].push_back({x, 0.9});
		}
	}

	updateMaxWeights();
}

void GraphicNetwork::updateMaxWeights()
{
	double max(0);
	double min(0);
	for (const WeightMatrix &matrix : weightMatrices)
	{
		for (const Vector &rowVector : matrix)
		{
			for (const double &value : rowVector)
			{
				if (value > max)
					max = value;
				else if (value < min)
					min = value;
			}
		}
	}
	maxWeight = max;
	minWeight = min;
}

void GraphicNetwork::scale_coordinates(const Cairo::RefPtr<Cairo::Context> &cr) const
{
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();
	cr->scale(width, height);
}

void GraphicNetwork::draw_network(const Cairo::RefPtr<Cairo::Context> &cr) const
{
	cr->set_source_rgb(0, 0, 0);
	cr->paint();

	cr->set_line_width(0.003);

	for (size_t l(0); l < numberOfNeuronLayers; ++l)
	{
		size_t layerSize(activations[l + 1].size());
		for (size_t j(0); j < layerSize; ++j)
		{
			size_t prevLayerSize(activations[l].size());
			for (size_t k(0); k < prevLayerSize; ++k)
			{
				double weight(weightMatrices[l][j][k]);
				if (weight >= 0)
				{
					if (maxWeight > 0)
						cr->set_source_rgb(0, weight / maxWeight, 0);
					else
						cr->set_source_rgb(0, 0, 0);
				}
				else
				{
					if (minWeight < 0)
						cr->set_source_rgb(weight / minWeight, 0, 0);
					else
						cr->set_source_rgb(0, 0, 0);
				}
				cr->move_to(nodeCoordinates[l + 1][j].x, nodeCoordinates[l + 1][j].y);
				cr->line_to(nodeCoordinates[l][k].x, nodeCoordinates[l][k].y);
				cr->stroke();
			}
			double bias(biases[l][j]);
			if (bias >= 0)
			{
				if (maxWeight > 0)
					cr->set_source_rgb(0, bias / maxWeight, 0);
				else
					cr->set_source_rgb(0, 0, 0);
			}
			else
			{
				if (minWeight < 0)
					cr->set_source_rgb(bias / minWeight, 0, 0);
				else
					cr->set_source_rgb(0, 0, 0);
			}
			cr->move_to(nodeCoordinates[l + 1][j].x, nodeCoordinates[l + 1][j].y);
			cr->line_to(nodeCoordinates[l].back().x, nodeCoordinates[l].back().y);
			cr->stroke();
		}
	}

	size_t totalNumberOfLayers(numberOfNeuronLayers + 1);
	for (size_t l(0); l < totalNumberOfLayers; ++l)
	{
		size_t activationSize(activations[l].size());
		for (size_t j(0); j < activationSize; ++j)
		{
			double value(activations[l][j] * 0.8);
			double x(nodeCoordinates[l][j].x);
			double y(nodeCoordinates[l][j].y);
			cr->set_source_rgb(value, value, value);
			cr->arc(x, y, nodeRadius, 0, 2 * M_PI);
			cr->fill();
			cr->set_source_rgb(0.8, 0.8, 0.8);
			cr->set_line_width(0.001);
			cr->arc(x, y, nodeRadius, 0, 2 * M_PI);
			cr->stroke();
		}
	}
	for (size_t l(0); l < numberOfNeuronLayers; ++l)
	{
		cr->set_source_rgb(0.8, 0.8, 0.8);
		cr->arc(nodeCoordinates[l].back().x, nodeCoordinates[l].back().y, nodeRadius * 0.7, 0, 2 * M_PI);
		cr->fill();
	}
}

bool GraphicNetwork::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
	scale_coordinates(cr);
	draw_network(cr);
	return true;
}

void GraphicNetwork::trainOnSample()
{
	const auto inputSetSize = inputData.size();
	if (inputSetSize != targetData.size())
	{
		throw std::runtime_error("The sizes of the input and target sets do not match!");
	}
	if (inputSetSize == 0)
	{
		throw std::runtime_error("There are no elements in the training set!");
	}
	
	std::size_t index{random() % inputSetSize};
	Vector input(inputData[index]);
	Vector target(targetData[index]);
	train(input, target);
	updateMaxWeights();
}

bool GraphicNetwork::on_redraw()
{
	trainOnSample();
	auto win = get_window();
	if (win)
	{
		Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
		win->invalidate_rect(r, false);
	}
	return true;
}
