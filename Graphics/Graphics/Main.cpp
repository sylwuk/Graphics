#include <iostream>
#include <memory>
#include <string>
#include "Shapes.h"
#include "Console.h"
#include "Window.h"
#include "ShapeFactory.h"
#include "Plot.h"
using namespace graphics;

//int main()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE previnstance, LPSTR lpcmdline, int ncmdshow)
{
	try
	{
		

		/*std::unique_ptr<Gui> window = std::make_unique<Window>(hInstance,
			"DesktopApp",
			"Shapes",
			1280,
			768,
			ncmdshow);*/
		//Plot plot{ std::move(window) };
		Plot plot{ std::make_unique<Window>(hInstance,
			"DesktopApp",
			"Shapes",
			1280,
			768,
			ncmdshow) };
		std::vector<int> vec;
		plot.add_x_axis(vec);
		std::unique_ptr<Gui> console = std::make_unique<Console>(100,100);
		/*window->add_shape<syl_shapes::Line>(syl_shapes::Line(std::make_pair(10, 20), std::make_pair(50, 40), 1, syl_shapes::color::RED));
		window->add_shape<syl_shapes::Line>(syl_shapes::Line(std::make_pair(100, 100), std::make_pair(150, 100), 2 ,syl_shapes::color::GREEN));
		window->add_shape<syl_shapes::Line>(syl_shapes::Line(std::make_pair(250, 150), std::make_pair(200, 300), 3, syl_shapes::color::BLUE));
		window->add_shape<syl_shapes::Line>(syl_shapes::Line(std::make_pair(400, 300), std::make_pair(400, 150), 4, syl_shapes::color::BLACK));
		window->add_shape<syl_shapes::Line>(syl_shapes::Line(std::make_pair(600, 150), std::make_pair(600, 400), 5, syl_shapes::color::ORANGE));
		window->add_shape<syl_shapes::Rectangle>(syl_shapes::Rectangle(std::make_pair(50, 50), std::make_pair(300, 300), 3, syl_shapes::color::PURPLE));*/
		//window->add_shape<syl_shapes::Rectangle>(syl_shapes::Rectangle(std::make_pair(70, 30), std::make_pair(200, 100), 10));
		//window->add_shape<syl_shapes::Rectangle>(syl_shapes::Rectangle(std::make_pair(5, 5), std::make_pair(0, 0), 1));
		//window->add_shape<syl_shapes::Line>(syl_shapes::Line(std::make_pair(20, 1), std::make_pair(0, 20)));
		/*Factory<Shape> factory;
		factory.create<syl_shapes::Rectangle>(0, 0, 10, 20);
	
		syl_shapes::Rectangle rect1(std::make_pair(10, 10), std::make_pair(3, 3));
		syl_shapes::Rectangle rect_copy(rect1);
		syl_shapes::Rectangle rect_assign(std::make_pair(1, 1), std::make_pair(3, 3));
		rect_assign = rect1;
		window->add_shape<syl_shapes::Rectangle>(std::move(rect1));
		window->add_shape<syl_shapes::Rectangle>(std::move(rect_copy));
		window->add_shape<syl_shapes::Rectangle>(std::move(rect_assign));
	
		window->add_shape<syl_shapes::Rectangle>(syl_shapes::Rectangle(std::make_pair(5, 5), std::make_pair(0, 0)));
		window->add_shape<syl_shapes::Line>(syl_shapes::Line(std::make_pair(20, 1), std::make_pair(0, 20)));
		window->add_shape<syl_shapes::Line>(syl_shapes::Line(std::make_pair(1, 2), std::make_pair(0, 30)));
		window->add_shape<syl_shapes::Line>(syl_shapes::Line(std::make_pair(1, 1), std::make_pair(10, 25)));
		window->add_shape<syl_shapes::Rectangle>(syl_shapes::Rectangle(std::make_pair(20, 10), std::make_pair(25, 0)));
		*/

		/*while (!window->terminate())
		{
			window->get_events();
			//window->draw();
		}*/
		plot.run();
	}
	catch (std::string &exeption)
	{
		MessageBox(
			NULL,
			(LPCSTR)exeption.c_str(),
			(LPCSTR)"Exeption",
			MB_ICONERROR | MB_OK | MB_DEFBUTTON1
		);
		return 1;
	}
	return 0;
}