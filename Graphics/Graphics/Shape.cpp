#include <string>
#include <iostream>

#include "Shape.h"

namespace syl_shapes
{

	Shape::Shape(
		//const std::pair<int, int>& size,
		const std::pair<int, int>& begin, color clr) :
		begin{ begin },
		clr{ clr }
	{
		//if (size.first < 0 || size.second < 0) throw std::string("size cannot be negative");
		if (begin.first < 0 || begin.second < 0) throw std::string("begin cannot be negative");
	}

	Shape::Shape(Shape&& src)
	{
		//size = std::move(src.size);
		begin = std::move(src.begin);
		clr = std::move(src.clr);
	}

	Shape::Shape(const Shape& src) : begin{ src.begin }
	{}

	Shape& Shape::operator=(const Shape& src)
	{
		begin = src.begin;
		clr = src.clr;
		return *this;
	}

	bool Shape::is_on_shape(int x, int y)
	{
		if (get_begin_x() == x && get_begin_y() == y) return true;
		return false;
	}

	void Shape::move(int x, int y)
	{
		if (begin.first < 0 || begin.second < 0) throw std::string("begin cannot be negative");
		begin.first = x;
		begin.second = y;
	}
}