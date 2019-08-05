#pragma once
#include <vector>
#include <memory>
#include <windows.h>

#include "Shapes.h"

void change_cursor_position(int x, int y);
void change_cursor_position(COORD position);

class Window
{
public:
	Window();
	~Window();
	template <class T,
		typename std::enable_if <std::is_base_of<syl_shapes::Shape, T>::value>::type* = nullptr>
	void add_shape(T&& shape)
	{
		shapes.push_back(std::make_shared<T>(std::forward<T>(shape)));
	}
	void delete_shape(int x, int y);
	void move_shape(int old_x, int old_y, int new_x, int new_y);
	void get_events();
	bool terminate();
	void get_cursor_position();
	void draw();
private:
	BOOL is_terminated;
	BOOL is_moving_shape;
	BOOL is_left_mouse_button_pressed;
	COORD cursor_position;
	HANDLE stdin_handle;
	DWORD fdwMode, fdwSaveOldMode;
	void key_event_handler(KEY_EVENT_RECORD event);
	void mouse_event_handler(MOUSE_EVENT_RECORD event);
	void move_cursor();
	void move_active_shape(COORD position);
	std::vector<std::shared_ptr<syl_shapes::Shape>> shapes;
	std::shared_ptr<syl_shapes::Shape> active_shape = nullptr;
};

