#pragma once
#include <utility>

#include "Shape.h"

namespace syl_shapes
{
	class Line : public Shape
	{
	public:
		Line(const std::pair<int, int>& begin,
			 const std::pair<int, int>& end,
			 int thickness,
			 color clr) : Shape(begin, clr), end_{ end }, thickness_{ thickness } {};
		Line(Line&&); //move constructor
		Line(const Line&); //copy constructor
		void resize(int width, int height) override;
		void resize(int length) override;
		void resize(const std::pair<int, int>& end);
		bool is_on_shape(int x, int y) override;
		void move(int x, int y) override;
		void draw(set_pos_callback set_pos, draw_callback draw_func) override;
		//int get_length() { return get_width(); };
		const int get_end_x(void) { return end_.first; };
		const int get_end_y(void) { return end_.second; };
		~Line() {};
	private:
		int thickness_;
		std::pair<int, int> end_; //x, y
	};
}

