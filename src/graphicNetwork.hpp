#ifndef GRAPHIC_NETWORK
#define GRAPHIC_NETWORK

#include "network.hpp"

#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>

struct Coordinate
{
	double x;
	double y;
};

class GraphicNetwork : public Network, public Gtk::DrawingArea
{
private:
	bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;
	bool on_redraw();

	std::vector<std::vector<Coordinate>> nodeCoordinates{};
	double nodeRadius;
	double maxWeight;
	double minWeight;

	// Hard-coded training samples, simulating an xor gate
	// TODO: this should be read from a file
	std::vector<Vector> inputData{{0, 0}, {0, 1}, {1, 0}, {1, 1}};
	std::vector<Vector> targetData{{0}, {1}, {1}, {0}};

	void updateMaxWeights();
	void scale_coordinates(const Cairo::RefPtr<Cairo::Context> &cr) const;
	void draw_network(const Cairo::RefPtr<Cairo::Context> &cr) const;
	void trainOnSample();

public:
	GraphicNetwork(const std::string &file, unsigned int timeout, const double &learningRate);
};

#endif
