#include <string>
#include <iostream>

#include "Line.h"

namespace syl_shapes
{
	Line::Line(Line&& src) :
		Shape(std::move(src))
	{

	}

	void Line::resize(int width, int height)
	{

	}

	void Line::resize(int length)
	{

	}

	bool Line::is_on_shape(int x, int y)
	{
		if (Shape::is_on_shape(x, y)) return true;
		return false;
	}

	void Line::draw(set_pos_callback set_pos)
	{
		set_pos(get_x(), get_y());
		for (int y = 0; y < get_height(); ++y)
		{
			set_pos(get_x(), get_y() + y);
			std::cout << std::string(get_length(), '*') << std::endl;
		}
	}
}