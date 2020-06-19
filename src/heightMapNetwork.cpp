#include "../include/heightMapNetwork.hpp"

#include <glibmm/main.h>
#include <iostream>

HeightMapGraphicNetwork::HeightMapGraphicNetwork(const std::string& file, unsigned int timeout, const double& learningRate) :
    GraphicNetwork(file, timeout, learningRate), deltaX(1.0 / 50), deltaY(deltaX) {

    if (activations.front().size() != 2) {
        throw std::runtime_error("Error creating a height map graphic network : the first layer must consist of two input neurons");
    }

    for (double x(1); x < 2; x += deltaX) {
        graphCoordinates.push_back(std::vector<Coordinate>(0));
        for (double y(0); y < 1; y += deltaY) {
            graphCoordinates.back().push_back({x, y});
        }
    }
}

HeightMapGraphicNetwork::~HeightMapGraphicNetwork() {}

void HeightMapGraphicNetwork::scale_coordinates(const Cairo::RefPtr<Cairo::Context>& cr) {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    cr->scale(width / 2, height);
}

bool HeightMapGraphicNetwork::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    scale_coordinates(cr);
    draw_network(cr);
    draw_graph(cr);
    return true;
}

void HeightMapGraphicNetwork::draw_graph(const Cairo::RefPtr<Cairo::Context>& cr) {
    for (const auto& vector : graphCoordinates) {
        for (const auto& coordinate : vector) {
            double x(coordinate.x);
            double y(coordinate.y);
            double result(predict({x - 1, y}).front());
            cr->set_source_rgb(result, result, result);
            cr->rectangle(x, y, x + deltaX, y + deltaY);
            cr->fill();
        }
    }
}
