#include <iostream>
#include <string>

#include "Rectangle.h"

namespace syl_shapes
{
	Rectangle::Rectangle(
		const std::pair<int, int>& top_left,
		const std::pair<int, int>& bottom_right,
		int thickness,
		color clr) :
		Shape(top_left, clr),
		bottom_right{ bottom_right },
		thickness{ thickness },
		lines{
		// Top line
		std::make_unique<Line>(Line(std::make_pair(top_left.first, top_left.second),
									std::make_pair(bottom_right.first, top_left.second), thickness, clr)),
		// Bottom line
		std::make_unique<Line>(Line(std::make_pair(top_left.first, bottom_right.second),
									std::make_pair(bottom_right.first, bottom_right.second), thickness, clr)),
		// Left line
		std::make_unique<Line>(Line(std::make_pair(top_left.first, top_left.second),
									std::make_pair(top_left.first, bottom_right.second), thickness, clr)),
		// Right line
		std::make_unique<Line>(Line(std::make_pair(bottom_right.first, top_left.second),
									std::make_pair(bottom_right.first, bottom_right.second+thickness-1), thickness, clr))
		}
	{
	}

	Rectangle::Rectangle(Rectangle&& src) :
		Shape(src),
		bottom_right{ std::move(src.bottom_right) },
		lines{ std::move(src.lines) },
		thickness{ std::move(src.thickness) }
	{
	}

	Rectangle::Rectangle(const Rectangle& src) :
		Shape(src),
		bottom_right{ src.bottom_right },
		thickness{ std::move(src.thickness) }
	{
		short index = 0;
		for (auto& line : src.lines)
		{
			lines[index++].reset(new Line(*line.get())); //copy lines
		}
	}

	Rectangle& Rectangle::operator=(const Rectangle& src)
	{
		short index = 0;
		for (auto& line : src.lines)
		{
			lines[index++].reset(new Line(*line.get())); //copy lines
		}

		Shape::operator=(src);

		return *this;
	}

	void Rectangle::move(int x, int y)
	{
		bottom_right.first -= get_begin_x() - x;
		bottom_right.second -= get_begin_y() - y;
		lines[0]->move(x, y);					 // Move top line
		lines[1]->move(x, bottom_right.second); // Move bottom line
		lines[2]->move(x, y);					 // Move left line
		lines[3]->move(bottom_right.first, y);  // Move right line

		Shape::move(x, y);
	}

	void Rectangle::draw(set_pos_callback set_pos, draw_callback draw_func)
	{
		for (auto& line : lines)
		{
			line->draw(set_pos, draw_func);
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