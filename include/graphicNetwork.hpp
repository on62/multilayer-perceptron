#ifndef GRAPHIC_NETWORK
#define GRAPHIC_NETWORK

#include "network.hpp"

#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>

struct Coordinate {
    double x;
    double y;
};

class GraphicNetwork : public Network, public Gtk::DrawingArea {
protected:
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    bool on_redraw();

    std::vector<std::vector<Coordinate>> nodeCoordinates;
    double nodeRadius;
    double maxWeight;
    double minWeight;

    void updateMaxWeights();
    virtual void scale_coordinates(const Cairo::RefPtr<Cairo::Context>& cr) const;
    void draw_network(const Cairo::RefPtr<Cairo::Context>& cr) const;
    void trainOnSample();
public:
    GraphicNetwork(const std::string& file, unsigned int timeout, const double& learningRate);
    virtual ~GraphicNetwork();
};

#endif
