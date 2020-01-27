#pragma once
#include <vector>
#include <memory>
#include <windows.h>

#include "Shapes.h"

namespace graphics
{
	class Gui
	{
	public:
		enum winColor : COLORREF
		{
			WHITE = RGB(255, 255, 255),
			BLACK = RGB(0, 0, 0),
			RED = RGB(255, 0, 0),
			GREEN = RGB(0, 255, 0),
			BLUE = RGB(0, 0, 255),
			YELLOW = RGB(255, 255, 0),
			ORANGE = RGB(255, 153, 0),
			PURPLE = RGB(102, 0, 102)
		};
	public:
		Gui(int width, int height);
		virtual ~Gui();
		template <class T,
			typename std::enable_if <std::is_base_of<syl_shapes::Shape, T>::value>::type* = nullptr>
			void add_shape(T&& shape)
		{
			shapes.push_back(std::make_shared<T>(std::forward<T>(shape)));
		}
		void delete_shape(int x, int y);
		void move_shape(int old_x, int old_y, int new_x, int new_y);
		int get_width() const { return size.first; };
		int get_height() const { return size.second; };
		bool terminate();
		static COLORREF color_decoder(syl_shapes::color);
		virtual void get_events() = 0;
		virtual void draw() = 0;
	protected:
		COORD cursor_position;
		BOOL is_terminated;
		BOOL is_moving_shape;
		BOOL is_left_mouse_button_pressed;
		void key_event_handler(KEY_EVENT_RECORD event);
		void mouse_event_handler(MOUSE_EVENT_RECORD event);
		void move_cursor();
		void move_active_shape(COORD position);
		void move_active_shape(int x, int y);
		std::vector<std::shared_ptr<syl_shapes::Shape>> shapes;
		std::shared_ptr<syl_shapes::Shape> active_shape = nullptr;
		std::pair<int, int> active_shape_offset;
		std::pair<int, int> size;
	};
}

