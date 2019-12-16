#pragma once
#include <tchar.h>
#include <memory>
#include "windows.h"
#include "Gui.h"

/*char ClassName[] = "myWindowClass";
HBRUSH hOrange = CreateSolidBrush(RGB(255, 180, 0));
HBRUSH hRed = CreateSolidBrush(RGB(255, 0, 0));
HBRUSH hYellow = CreateSolidBrush(RGB(255, 255, 0));*/

class Window : public Gui
{
public:
	Window(HINSTANCE hInstance, const char* windowClass, const char* title, int ncmds);
	~Window();
	virtual void get_events() override;
	virtual void draw() override;
	static LRESULT CALLBACK WndProcWrapper(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	HWND hWnd;
	WNDCLASSEX wcex;
	HINSTANCE hInst;
	std::unique_ptr<TCHAR> szWindowClass;
	std::unique_ptr<TCHAR> szTitle;
	int nCmdShow;
};

