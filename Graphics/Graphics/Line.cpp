#include <string>
#include <iostream>
#include <cmath>

#include "Line.h"

namespace syl_shapes
{
	Line::Line(Line&& src) :
		Shape(std::move(src)),
		end_{ std::move(src.end_) },
		thickness_{ std::move(src.thickness_) }
	{

	}

	Line::Line(const Line& src) :
		Shape(src),
		end_{ src.end_ },
		thickness_{ src.thickness_ }
	{

	}

	void Line::resize(int width, int height)
	{

	}

	void Line::resize(int length)
	{

	}

	void Line::resize(const std::pair<int, int>& end)
	{
		end_ = end;
	}

	void Line::move(int x, int y)
	{	
		//std::cout << "moving line old endx: " << end_.first << " old endy: " << end_.second;
		end_.first -= get_begin_x() - x;
		end_.second -= get_begin_y() - y;
		//std::cout << " new endx: " << end_.first << " new endy: " << end_.second << std::endl;
		Shape::move(x, y);
		
	}

	bool Line::is_on_shape(int x, int y)
	{
		if (Shape::is_on_shape(x, y)) return true;
		/*if (x >= get_x() && x <= (get_x() + get_length()) &&
			y >= get_y() && y <= (get_y() + get_height())) return true;*/
		return false;
	}

	void Line::draw(set_pos_callback set_pos, draw_callback draw_func)
	{
		double dx = get_end_x() - get_begin_x();
		double dy = get_end_y() - get_begin_y();
		double adx = abs(dx);
		double ady = abs(dy);
		double sx = 0, sy = 0;

		if (dx == 0)
		{
			sx = 0;
			sy = 1;
		}
		else if (dy == 0)
		{
			sx = 1;
			sy = 0;
		}
		else if (adx == ady)
		{
			sx = 1;
			sy = 1;
		}
		else if (adx > ady)
		{
			sx = 1;
			sy = (adx ) / (ady );
		}
		else if (adx < ady)
		{
			sx = (ady ) / (adx );
			sy = 1;
		}
		
		sx = dx < 0 ? -sx : sx;
		sy = dy < 0 ? -sy : sy;

		for (int layer = 0; layer < thickness_; ++layer)
		{
			int bx = adx >= ady ? get_begin_x() : get_begin_x() + layer;
			int by = adx < ady ? get_begin_y() : get_begin_y() + layer;
			int ex = adx >= ady ? get_end_x() : get_end_x() + layer;
			int ey = adx < ady ? get_end_y() : get_end_y() + layer;
			int cx = bx, cy = by;
			int pixel = 0;
			do
			{
				//std::cout << "cx: " << cx << "cy:" << cy << "ex" << get_end_x() << "ey" << get_end_y() << "dx:" << dx << "dy:" << dy << "sx:" << sx << "sy:" << sy << "i/sx" << pixel << std::endl;
				draw_func(cx, cy, get_color());
				cx = dx == 0 ? cx : bx + static_cast<int>(ceil(pixel / sx));
				cy = dy == 0 ? cy : by + static_cast<int>(ceil(pixel / sy));
				++pixel;
			} while (cx != ex || cy != ey);
			draw_func(cx, cy, get_color());
		}
		
	}
}