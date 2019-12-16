#pragma once
#include <utility>

#include "Shape.h"

namespace syl_shapes
{
	class Line : public Shape
	{
	public:
		Line(const std::pair<int, int>& size,
			 const std::pair<int, int>& position) : Shape(size, position) {};
		Line(Line&&); //move constructor
		void resize(int width, int height) override;
		void resize(int length) override;
		bool is_on_shape(int x, int y) override;
		void draw(set_pos_callback set_pos) override;
		int get_length() { return get_width(); };
		~Line() {};
	};
}

