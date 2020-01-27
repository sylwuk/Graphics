#include <type_traits>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

#include "Gui.h"


namespace graphics
{
	Gui::Gui(int width, int height) :
		is_terminated(false),
		is_moving_shape(false),
		is_left_mouse_button_pressed(false),
		size{ std::make_pair(width, height) }
	{

	}

	Gui::~Gui()
	{
		is_terminated = true;
	}

	// Delete shape on position x,y
	void Gui::delete_shape(int x, int y)
	{
		auto shape = std::find_if(shapes.begin(), shapes.end(),
			[&](std::shared_ptr<syl_shapes::Shape>& shape) {
			return (shape->get_begin_x() == x) && (shape->get_begin_y() == y);
		});

		if (shape != shapes.end()) shapes.erase(shape);
	}

	// Move shape on position x equal old_x and y equal old_y
	// to new position x equal new_x and y equal new_y
	void Gui::move_shape(int old_x, int old_y, int new_x, int new_y)
	{
		for (auto& shape : shapes)
		{
			if ((shape->get_begin_x() == old_x) && (shape->get_begin_y() == old_y))
			{
				shape->move(new_x, new_y);
				return;
			}
		}
	}

	void Gui::move_active_shape(COORD position)
	{
		// Move shape with adjustment for initial mouse position in relation to shape start position
		active_shape->move(position.X - active_shape_offset.first,
			position.Y - active_shape_offset.second);
	}

	void Gui::move_active_shape(int x, int y)
	{
		// Move shape with adjustment for initial mouse position in relation to shape start position
		active_shape->move(x - active_shape_offset.first,
			y - active_shape_offset.second);
	}

	void Gui::move_cursor()
	{
		//std::cout << GetAsyncKeyState(VK_LEFT) << std::endl;
	}

	// Handles keyboard events
	void Gui::key_event_handler(KEY_EVENT_RECORD event)
	{
		if (event.bKeyDown) // Only when the key is pressed down
		{
			switch (event.wVirtualKeyCode)
			{
			case VK_ESCAPE:
				is_terminated = true;
				break;
			case VK_LEFT:
				if (!is_moving_shape && cursor_position.X > 0) --cursor_position.X;
				break;
			case VK_RIGHT:
				if (!is_moving_shape) ++cursor_position.X;
				break;
			case VK_UP:
				if (!is_moving_shape && cursor_position.Y > 0) --cursor_position.Y;
				break;
			case VK_DOWN:
				if (!is_moving_shape) ++cursor_position.Y;
				break;
			case VK_F1:
				is_moving_shape = !is_moving_shape;
				break;
			case VK_DELETE:
				if (active_shape != nullptr)
				{
					delete_shape(active_shape->get_begin_x(), active_shape->get_begin_y());
					active_shape = nullptr;
				}
				break;
			default:
				break; // Unsupported key.
			}
		}
	}

	void Gui::mouse_event_handler(MOUSE_EVENT_RECORD event)
	{
		if (is_left_mouse_button_pressed && active_shape != nullptr && event.dwEventFlags == MOUSE_MOVED)
		{
			move_active_shape(event.dwMousePosition);
		}
		else
		{
			// If we get mouse event other than move when moving shape it means the shape is released
			if (is_left_mouse_button_pressed && active_shape != nullptr) active_shape = nullptr;
			switch (event.dwButtonState)
			{
			case FROM_LEFT_1ST_BUTTON_PRESSED:

				is_left_mouse_button_pressed = !is_left_mouse_button_pressed;
				if (is_left_mouse_button_pressed)
				{
					for (auto& shape : shapes)
					{
						if (shape->is_on_shape(event.dwMousePosition.X, event.dwMousePosition.Y))
						{
							active_shape = shape;
							// Save mouse posission offset in relation to shape starting position
							// This is done to properly draw shape regardless of where mouse grabs it
							active_shape_offset.first = event.dwMousePosition.X - shape->get_begin_x();
							active_shape_offset.second = event.dwMousePosition.Y - shape->get_begin_y();
							break;
						}
					}
				}
				break;
			}
		}
	}

	COLORREF Gui::color_decoder(syl_shapes::color color)
	{
		switch (color)
		{
		case syl_shapes::color::WHITE:
			return winColor::WHITE;
		case syl_shapes::color::BLACK:
			return winColor::BLACK;
		case syl_shapes::color::RED:
			return winColor::RED;
		case syl_shapes::color::GREEN:
			return winColor::GREEN;
		case syl_shapes::color::BLUE:
			return winColor::BLUE;
		case syl_shapes::color::YELLOW:
			return winColor::YELLOW;
		case syl_shapes::color::ORANGE:
			return winColor::ORANGE;
		case syl_shapes::color::PURPLE:
			return winColor::PURPLE;
		}
		return winColor::WHITE;
	}

	// Terminates the window if ESC key is pressed
	bool Gui::terminate()
	{
		return is_terminated;
	}
}