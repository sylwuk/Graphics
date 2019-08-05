#pragma once
#include <utility>

#include "Shape.h"

namespace syl_shapes
{
	class Line : public Shape
	{
	public:
		Line(std::pair<int, int> size, std::pair<int, int> position) : Shape(std::move(size), std::move(position)) {};
		Line(Line&&); //move constructor
		virtual void resize(int width, int height);
		virtual void resize(int length);
		virtual bool is_on_shape(int x, int y);
		virtual void draw(set_pos_callback set_pos);
		int get_length() { return get_width(); };
		virtual ~Line() {};
	};
}

