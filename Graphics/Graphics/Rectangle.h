#pragma once
#include <array>
#include <memory>
#include <utility>

#include "Shape.h"
#include "Line.h"

namespace syl_shapes
{
	class Rectangle : public Shape
	{
	public:
		Rectangle(
			const std::pair<int, int>& top_left,
			const std::pair<int, int>& bottom_right,
			int thickness,
			color clr);
		Rectangle(Rectangle&&); //move constructor
		Rectangle(const Rectangle&); //copy constructor
		Rectangle& operator=(const Rectangle&);
		void move(int x, int y) override;
		void resize(int width, int height) override;
		void resize(int length) override;
		bool is_on_shape(int x, int y) override;
		void draw(set_pos_callback set_pos, draw_callback draw_func) override;
		~Rectangle() {};
	private:
		int thickness;
		std::array<std::unique_ptr<Line>, 4> lines;
		std::pair<int, int> bottom_right; //x, y
	};
}