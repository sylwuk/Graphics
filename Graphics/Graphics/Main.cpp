#include <iostream>
#include <memory>
#include <string>
#include "Shapes.h"
#include "Window.h"



class test
{
public:
	test() {};
};

void main()
{
	Window window;
	
	try
	{
		window.add_shape<syl_shapes::Rectangle>(syl_shapes::Rectangle(std::make_pair(5, 5), std::make_pair(0, 0)));
		window.add_shape<syl_shapes::Line>(syl_shapes::Line(std::make_pair(20, 1), std::make_pair(0, 20)));
		window.add_shape<syl_shapes::Line>(syl_shapes::Line(std::make_pair(1, 2), std::make_pair(0, 30)));
		window.add_shape<syl_shapes::Line>(syl_shapes::Line(std::make_pair(1, 1), std::make_pair(10, 25)));
		window.add_shape<syl_shapes::Rectangle>(syl_shapes::Rectangle(std::make_pair(20, 10), std::make_pair(25, 0)));
	}
	catch(std::string exeption)
	{
		std::cout << exeption << std::endl;
		return;
	}
	while (!window.terminate())
	{
		window.get_events();
		window.draw();
	}
}