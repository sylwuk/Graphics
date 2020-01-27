#pragma once
#include <tchar.h>
#include <memory>
#include "windows.h"
#include "Gui.h"

/*char ClassName[] = "myWindowClass";
HBRUSH hOrange = CreateSolidBrush(RGB(255, 180, 0));
HBRUSH hRed = CreateSolidBrush(RGB(255, 0, 0));
HBRUSH hYellow = CreateSolidBrush(RGB(255, 255, 0));*/

namespace graphics
{
	class Window : public Gui
	{
	public:
		Window(HINSTANCE hInstance,
			const TCHAR windowClass[],
			const TCHAR title[],
			int width,
			int height,
			int ncmds);
		~Window();
		virtual void get_events() override;
		virtual void draw() override;
		static LRESULT CALLBACK WndProcWrapper(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		static void drawShape(int x, int y, syl_shapes::color);
		static void eraseShape(int x, int y, syl_shapes::color);
	private:
		LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	private:
		HWND hWnd;
		//HDC context;
		WNDCLASSEX wcex;
		HINSTANCE hInst;
		std::unique_ptr<TCHAR> szWindowClass;
		std::unique_ptr<TCHAR> szTitle;
		int nCmdShow;
	};
}
