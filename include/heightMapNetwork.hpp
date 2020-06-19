#ifndef HEIGHT_MAP_NETWORK
#define HEIGHT_MAP_NETWORK

#include "graphicNetwork.hpp"
#include <string>
#include <vector>

class HeightMapGraphicNetwork : public GraphicNetwork {
private:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    bool on_redraw();
    void scale_coordinates(const Cairo::RefPtr<Cairo::Context>& cr);
    void draw_graph(const Cairo::RefPtr<Cairo::Context>& cr);

    std::vector<std::vector<Coordinate>> graphCoordinates;
    double deltaX;
    double deltaY;
public:
    HeightMapGraphicNetwork(const std::string& file, unsigned int timeout, const double& learningRate);
    ~HeightMapGraphicNetwork();
};

#endif
