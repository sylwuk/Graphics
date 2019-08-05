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
			std::pair<int, int>&& size,
			std::pair<int, int>&& position);
		Rectangle(Rectangle&&);
		virtual void move(int x, int y) override;
		virtual void resize(int width, int height) override;
		virtual void resize(int length) override;
		virtual bool is_on_shape(int x, int y) override;
		virtual void draw(set_pos_callback set_pos) override;
		virtual ~Rectangle() {};
	private:
		std::array<std::unique_ptr<Line>, 4> lines;
	};
}