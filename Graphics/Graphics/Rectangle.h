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
			const std::pair<int, int>& size,
			const std::pair<int, int>& position);
		Rectangle(Rectangle&&); //move constructor
		Rectangle(const Rectangle&); //copy constructor
		Rectangle& operator=(const Rectangle&);
		void move(int x, int y) override;
		void resize(int width, int height) override;
		void resize(int length) override;
		bool is_on_shape(int x, int y) override;
		void draw(set_pos_callback set_pos) override;
		~Rectangle() {};
	private:
		std::array<std::unique_ptr<Line>, 4> lines;
	};
}