#include <iostream>
#include "Console.h"

namespace
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	HDC console_context = GetDC(GetConsoleWindow());
}

namespace graphics
{
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

	void drawShape(int x, int y, syl_shapes::color)
	{
		std::cout << "*";
		//SetPixel(console_context, x, y, RGB(255, 0, 0));
	}

	Console::Console(int width, int height) :
		stdin_handle(GetStdHandle(STD_INPUT_HANDLE)),
		Gui{ width, height }
	{
		// If AllocConsole succeedes it means that it is Windows application
		// so we need to spawn a console and redirect I/O to it
		if (AllocConsole())
		{
			freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
			SetConsoleTitle("Shapes");
			sb = std::cout.rdbuf(&ob);
			console = GetStdHandle(STD_OUTPUT_HANDLE);
			stdin_handle = GetStdHandle(STD_INPUT_HANDLE);
			console_context = GetDC(GetConsoleWindow());
		}

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

	Console::~Console()
	{
		// Restore input mode on exit.
		SetConsoleMode(stdin_handle, fdwSaveOldMode);

		if (sb) std::cout.rdbuf(sb);
	}

	void Console::draw()
	{
		system("cls");
		if (!SetConsoleMode(stdin_handle, fdwMode)) throw std::string("Could not set console mode.");
		get_cursor_position();
		for (auto& shape : shapes)
		{
			change_cursor_position(shape->get_begin_x(), shape->get_begin_y());
			shape->draw(change_cursor_position, drawShape);
		}
		// Reset cursor position to original state
		change_cursor_position(cursor_position);
	}

	void Console::get_cursor_position()
	{
		CONSOLE_SCREEN_BUFFER_INFO screen_buffer;
		if (!GetConsoleScreenBufferInfo(console, &screen_buffer)) throw std::string("Cannot get screen buffer info.");

		cursor_position = screen_buffer.dwCursorPosition;
	}

	// Receives window events
	void Console::get_events()
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
}