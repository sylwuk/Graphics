#pragma once
#include <vector>
#include "Shape.h"
#include "Rectangle.h"
/*
namespace games
{
	class SlotMachine : public syl_shapes::Shape
	{
	public:
		SlotMachine(
			std::pair<int, int>&& size,
			std::pair<int, int>&& position);
		SlotMachine(SlotMachine&&);
		void move(int x, int y) override;
		void resize(int width, int height) override;
		void resize(int length) override;
		bool is_on_shape(int x, int y) override;
		void draw(set_pos_callback set_pos) override;
		~SlotMachine() {};
	private:
		enum class symbols : short
		{
			DIAMOND = 0,
			LEMON,
			WATERMELON,
			HEART,
			SEVEN,
			BELL,
			HORSESHOE,
			CHERRIES,
			BAR
		};

		class Slot : public syl_shapes::Shape
		{
		public:
			Slot(
				std::pair<int, int>&& size,
				std::pair<int, int>&& position);
			Slot(Slot&&);
			void move(int x, int y) override;
			void resize(int width, int height) override;
			void resize(int length) override;
			bool is_on_shape(int x, int y) override;
			void draw(set_pos_callback set_pos) override;
			~Slot() {};
		private:
			syl_shapes::Rectangle area;
		};
		std::vector<Slot> slots;
		syl_shapes::Rectangle area;
	};
}
*/