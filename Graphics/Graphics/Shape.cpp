#include <string>
#include <iostream>

#include "Shape.h"

namespace syl_shapes
{

	Shape::Shape(
		const std::pair<int, int>& size,
		const std::pair<int, int>& position) :
		size{ size }, position{ position }
	{
		if (size.first < 0 || size.second < 0) throw std::string("size cannot be negative");
		if (position.first < 0 || position.second < 0) throw std::string("position cannot be negative");
	}

	Shape::Shape(Shape&& src)
	{
		size = std::move(src.size);
		position = std::move(src.position);
	}

	Shape::Shape(const Shape& src) :
		size{ src.size }, position{ src.position }
	{}

	Shape& Shape::operator=(const Shape& src)
	{
		size = src.size;
		position = src.position;
		return *this;
	}

	bool Shape::is_on_shape(int x, int y)
	{
		if (get_x() == x && get_y() == y) return true;
		return false;
	}

	void Shape::move(int x, int y)
	{
		if (position.first < 0 || position.second < 0) throw std::string("position cannot be negative");
		position.first = x;
		position.second = y;
	}
}