#include <string> 
#include <iostream>
#include <windowsx.h>
#include "Window.h"

HDC context;

namespace graphics
{
	Window::Window(HINSTANCE hInstance,
		const TCHAR windowClass[],
		const TCHAR title[],
		int width,
		int height,
		int ncmds) :
		nCmdShow{ ncmds },
		szWindowClass{ new TCHAR[_tcslen(windowClass) + 1] },
		szTitle{ new TCHAR[_tcslen(title) + 1] },
		Gui{ width, height }
	{

		_tcscpy_s(szWindowClass.get(), _tcslen(windowClass) + 1, windowClass);
		_tcscpy_s(szTitle.get(), _tcslen(title) + 1, title);
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = Window::WndProcWrapper;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = szWindowClass.get();
		wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

		if (!RegisterClassEx(&wcex)) throw std::string("Call to RegisterClassEx failed!");

		// Store instance handle
		hInst = hInstance;

		// The parameters to CreateWindow explained:
		// szWindowClass: the name of the application
		// szTitle: the text that appears in the title bar
		// WS_OVERLAPPEDWINDOW: the type of window to create
		// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
		// 500, 100: initial size (width, length)
		// NULL: the parent of this window
		// NULL: this application dows not have a menu bar
		// hInstance: the first parameter from WinMain
		// NULL: not used in this application
		hWnd = CreateWindow(
			szWindowClass.get(),
			szTitle.get(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			size.first, size.second,
			NULL,
			NULL,
			hInstance,
			this
		);

		if (!hWnd) throw std::string("Call to CreateWindow failed!");
		HDC hdc;
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);
		SetBkColor(hdc, RGB(0, 0, 0));
		EndPaint(hWnd, &ps);
		context = GetDC(hWnd);

		// The parameters to ShowWindow explained:
		// hWnd: the value returned from CreateWindow
		// nCmdShow: the fourth parameter from WinMain
		ShowWindow(hWnd,
			nCmdShow);
		UpdateWindow(hWnd);
	}

	Window::~Window()
	{
	}

	void Window::get_events()
	{
		MSG msg;
		GetMessage(&msg, NULL, 0, 0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		//UpdateWindow(hWnd);
	}

	void Window::draw()
	{
		//UpdateWindow(hWnd);
		for (auto& shape : shapes)
		{
			//change_cursor_position(shape->get_x(), shape->get_y());
			shape->draw(nullptr, drawShape);
		}

	}

	LRESULT CALLBACK Window::WndProcWrapper(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		Window *pThis; // our "this" pointer will go here
		if (message == WM_NCCREATE) {
			// Recover the "this" pointer which was passed as a parameter
			// to CreateWindow(Ex).
			LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
			pThis = static_cast<Window*>(lpcs->lpCreateParams);
			// Put the value in a safe place for future use
			SetWindowLongPtr(hWnd, GWLP_USERDATA,
				reinterpret_cast<LONG_PTR>(pThis));
		}
		else {
			// Recover the "this" pointer from where our WM_NCCREATE handler
			// stashed it.
			pThis = reinterpret_cast<Window*>(
				GetWindowLongPtr(hWnd, GWLP_USERDATA));
		}
		if (pThis)
		{
			if (message == WM_DESTROY) pThis->is_terminated = true;
			// Now that we have recovered our "this" pointer, let the
			// member function finish the job.
			return pThis->WndProc(hWnd, message, wParam, lParam);
		}
		// We don't know what our "this" pointer is, so just do the default
		// thing. Hopefully, we didn't need to customize the behavior yet.
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_PAINT:
			draw();
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_LBUTTONDOWN:
			is_left_mouse_button_pressed = true;
			std::cout << "dupa x: " << GET_X_LPARAM(lParam) << " y: " << GET_Y_LPARAM(lParam) << std::endl;
			for (auto& shape : shapes)
			{
				if (shape->is_on_shape(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)))
				{
					std::cout << "on shape!" << std::endl;
					active_shape = shape;
					// Save mouse posission offset in relation to shape starting position
					// This is done to properly draw shape regardless of where mouse grabs it
					active_shape_offset.first = GET_X_LPARAM(lParam) - shape->get_begin_x();
					active_shape_offset.second = GET_Y_LPARAM(lParam) - shape->get_begin_y();
					break;
				}
			}
			break;
		case WM_LBUTTONUP:
			is_left_mouse_button_pressed = false;
			active_shape = nullptr;
			break;
		case WM_MOUSEMOVE:
			if (is_left_mouse_button_pressed && active_shape != nullptr)
			{
				active_shape->draw(nullptr, eraseShape);
				move_active_shape(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}

		return 0;
	}

	void Window::drawShape(int x, int y, syl_shapes::color color)
	{
		SetPixel(context, x, y, color_decoder(color));
	}

	void Window::eraseShape(int x, int y, syl_shapes::color)
	{
		SetPixel(context, x, y, RGB(255, 255, 255));
	}
}