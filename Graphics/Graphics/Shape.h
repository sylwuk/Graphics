#pragma once
#include <utility>

using set_pos_callback = void(*)(int, int);

namespace syl_shapes
{
	class Shape
	{
	public:
		Shape(std::pair<int, int>&& size,
			std::pair<int, int>&& position);
		Shape(Shape&&);
		virtual void move(int x, int y);
		virtual void resize(int width, int height) = 0;
		virtual void resize(int length) = 0;
		virtual void draw(set_pos_callback) = 0;
		virtual bool is_on_shape(int x, int y);
		const int get_width() { return size.first; };
		const int get_height() { return size.second; };
		const int get_x() { return position.first; };
		const int get_y() { return position.second; };
		virtual ~Shape() {};
	private:
		std::pair<int, int> size; //width, height
		std::pair<int, int> position; //x, y
	};
}