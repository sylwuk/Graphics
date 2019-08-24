#include <type_traits>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

#include "Window.h"

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

Window::Window() :
	stdin_handle(GetStdHandle(STD_INPUT_HANDLE)), 
	is_terminated(false),
	is_moving_shape(false),
	is_left_mouse_button_pressed(false)
{
	// Check validity of input handle
	if (stdin_handle == INVALID_HANDLE_VALUE) throw std::string("Could not get input handle.");

	// Save the current input mode, to be restored on exit. 
	if (!GetConsoleMode(stdin_handle, &fdwSaveOldMode)) throw std::string("Could not save console mode.");

	// Enable the window and mouse input events. 
	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(stdin_handle, fdwMode)) throw std::string("Could not set console mode.");

	//SetFocus(GetConsoleWindow());

	SMALL_RECT windowSize = { 0, 0, 70, 40 };

	SetConsoleWindowInfo(console, TRUE, &windowSize);


	get_cursor_position();
}

Window::~Window()
{
	is_terminated = true;
	// Restore input mode on exit.
	SetConsoleMode(stdin_handle, fdwSaveOldMode);
}

// Sets proper start position of drawing the shape in the console
// Has to be execuded for every new line in a shape
void change_cursor_position(int x, int y)
{
	COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(console, coord);
}

void change_cursor_position(COORD position)
{
	SetConsoleCursorPosition(console, position);
}

void Window::draw()
{
	system("cls");
	if (!SetConsoleMode(stdin_handle, fdwMode)) throw std::string("Could not set console mode.");
	for (auto& shape : shapes)
	{
		change_cursor_position(shape->get_x(), shape->get_y());
		shape->draw(change_cursor_position);
	}
	// Reset cursor position to original state
	change_cursor_position(cursor_position);
}

// Delete shape on position x,y
void Window::delete_shape(int x, int y)
{
	auto shape = std::find_if(shapes.begin(), shapes.end(),
		[&](std::shared_ptr<syl_shapes::Shape>& shape) {
			return (shape->get_x() == x) && (shape->get_y() == y);
		});
	
	if (shape != shapes.end()) shapes.erase(shape);
}

// Move shape on position x equal old_x and y equal old_y
// to new position x equal new_x and y equal new_y
void Window::move_shape(int old_x, int old_y, int new_x, int new_y)
{
	for (auto& shape : shapes)
	{
		if ((shape->get_x() == old_x) && (shape->get_y() == old_y))
		{
			shape->move(new_x, new_y);
			return;
		}
	}
}

void Window::move_active_shape(COORD position)
{
	// Move shape with adjustment for initial mouse position in relation to shape start position
	active_shape->move(position.X - active_shape_offset.first, 
					   position.Y - active_shape_offset.second);
}

void Window::move_cursor()
{
	//std::cout << GetAsyncKeyState(VK_LEFT) << std::endl;
}

void Window::get_cursor_position()
{
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer;
	if (!GetConsoleScreenBufferInfo(console, &screen_buffer)) throw std::string("Cannot get screen buffer info.");

	cursor_position = screen_buffer.dwCursorPosition;
}

// Handles keyboard events
void Window::key_event_handler(KEY_EVENT_RECORD event)
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
				delete_shape(active_shape->get_x(), active_shape->get_y());
				active_shape = nullptr;
			}
			break;
		default:
			break; // Unsupported key.
		}
	}
}

void Window::mouse_event_handler(MOUSE_EVENT_RECORD event)
{
	if (is_left_mouse_button_pressed && active_shape != nullptr && event.dwEventFlags == MOUSE_MOVED)
	{
		move_active_shape(event.dwMousePosition);
	}
	else
	{
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
						active_shape_offset.first = event.dwMousePosition.X - shape->get_x();
						active_shape_offset.second = event.dwMousePosition.Y - shape->get_y();
						break;
					}
				}
			}
			break;
		}
	}
}

// Receives window events
void Window::get_events()
{
	DWORD num_read;
	INPUT_RECORD input_buffer[128];

	ReadConsoleInput(stdin_handle,      // input buffer handle 
					 input_buffer,      // buffer to read into 
					 128,				    // size of read buffer 
					 &num_read);		// number of records read 

	// Dispatch the events to the appropriate handler. 
	for (DWORD i = 0; i < num_read; i++)
	{
		switch (input_buffer[i].EventType)
		{
		case KEY_EVENT: // keyboard input 
			key_event_handler(input_buffer[i].Event.KeyEvent);
			break;

		case MOUSE_EVENT: // mouse input 
			mouse_event_handler(input_buffer[i].Event.MouseEvent);
			break;

		case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing
		case FOCUS_EVENT:  // disregard focus events 
		case MENU_EVENT:   // disregard menu events 
		default:
			break;
		}
	}
}

// Terminates the window if ESC key is pressed
bool Window::terminate()
{
	return is_terminated;
}