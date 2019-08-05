#include <iostream>
#include <string>

#include "Rectangle.h"

namespace syl_shapes
{
	Rectangle::Rectangle(
		std::pair<int, int>&& size,
		std::pair<int, int>&& position) :
		Shape(std::move(size), std::move(position)),
		lines{
		// Top line
		std::make_unique<Line>(Line(std::make_pair(size.first, 1),
									std::make_pair(position.first, position.second))),
		// Bottom line
		std::make_unique<Line>(Line(std::make_pair(size.first, 1),
									std::make_pair(position.first, position.second + size.second - 1))),
		// Left line
		std::make_unique<Line>(Line(std::make_pair(1, size.second),
									std::make_pair(position.first, position.second))),
		// Right line
		std::make_unique<Line>(Line(std::make_pair(1, size.second),
									std::make_pair(position.first + size.first - 1, position.second)))
		}
	{
	}

	Rectangle::Rectangle(Rectangle&& src) :
		Shape(std::move(src)),
		lines(std::move(src.lines))
	{
	}

	void Rectangle::move(int x, int y)
	{
		lines[0]->move(x, y);					 // Move top line
		lines[1]->move(x, y + get_height() - 1); // Move bottom line
		lines[2]->move(x, y);					 // Move left line
		lines[3]->move(x + get_width() - 1, y);  // Move right line
		Shape::move(x, y);
	}

	void Rectangle::draw(set_pos_callback set_pos)
	{
		for (auto& line : lines)
		{
			line->draw(set_pos);
		}
	}

	bool Rectangle::is_on_shape(int x, int y)
	{
		if (Shape::is_on_shape(x, y)) return true;
		else
		{
			for (auto& line : lines)
			{
				if (line->is_on_shape(x, y)) return true;
			}
		}
		return false;
	}

	void Rectangle::resize(int width, int height)
	{

	};

	void Rectangle::resize(int length)
	{

	};
}