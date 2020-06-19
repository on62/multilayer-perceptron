#include "../include/graphicNetwork.hpp"
#include "../include/heightMapNetwork.hpp"
#include "../include/window.hpp"

#include <gtkmm/application.h>
#include <gtkmm/main.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

    Gtk::Main app(argc, argv);
    Window win;
    win.set_title("Neural Network");
    const int width(200);
    win.resize(2 * width, width);

    createRandomFile("../files/file.txt", {2, 10, 1}, time(0));

    HeightMapGraphicNetwork network("../files/file.txt", 1, 0.1);

    win.add(network);
    network.show();

    Gtk::Main::run(win);

    return 0;
}
