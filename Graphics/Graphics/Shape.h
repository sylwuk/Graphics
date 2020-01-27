#pragma once
#include <utility>

namespace syl_shapes
{
	enum class color
	{
		WHITE,
		BLACK,
		RED,
		GREEN,
		BLUE,
		YELLOW,
		ORANGE,
		PURPLE
	};
}

using set_pos_callback = void(*)(int, int);
using draw_callback = void(*)(int, int, syl_shapes::color);

namespace syl_shapes
{
	class Shape
	{
	public:
		Shape(const std::pair<int, int>& begin, color clr);

		// Rule of five
		Shape(Shape&&); //move constructor
		Shape(const Shape&); //copy constructor
		virtual Shape& operator=(const Shape&);
		virtual void move(int x, int y);
		virtual void resize(int width, int height) = 0;
		virtual void resize(int length) = 0;
		virtual void draw(set_pos_callback, draw_callback) = 0;
		virtual bool is_on_shape(int x, int y);
		//virtual const int get_width() = 0;
		//virtual const int get_height() = 0;
		const int get_begin_x(void) { return begin.first; };
		const int get_begin_y(void) { return begin.second; };
		const color get_color(void) { return clr; };
		virtual ~Shape() {};
	protected:
		//std::pair<int, int> size; //width, height
		std::pair<int, int> begin; //x, y
		color clr;
	};
}