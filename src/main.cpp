#include "graphicNetwork.hpp"

#include <gtkmm/window.h>
#include <gtkmm/application.h>
#include <iostream>

using namespace std;

int main()
{
	try
	{
		constexpr auto width = 600u;
		constexpr auto height = width;
		constexpr auto learningRate = 0.1;
		constexpr auto timeout = 1u; // 1ms
		constexpr auto filename = "weight_data/file.txt";
		const auto networkLayout = {2ul, 10ul, 1ul};

		auto app = Gtk::Application::create();

		Gtk::Window win;
		win.set_title("Multi-layer Perceptron Network");
		win.resize(width, height);

		createRandomFile(filename, networkLayout);

		GraphicNetwork network(filename, timeout, learningRate);

		win.add(network);
		network.show();
		app->run(win);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
