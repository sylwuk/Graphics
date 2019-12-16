#include <string.h> 
#include "Window.h"

Window::Window(HINSTANCE hInstance, const TCHAR windowClass[], const TCHAR title[], int ncmds) :
	nCmdShow{ ncmds },
	szWindowClass{ new TCHAR[_tcslen(windowClass)+1] },
	szTitle{ new TCHAR[_tcslen(title)+1] }
{

	_tcscpy_s(szWindowClass.get(), _tcslen(windowClass)+1, windowClass);
	_tcscpy_s(szTitle.get(), _tcslen(title)+1, title);
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
		500, 100,
		NULL,
		NULL,
		hInstance,
		this
	);

	if (!hWnd) throw std::string("Call to CreateWindow failed!");

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
}

void Window::draw()
{
	UpdateWindow(hWnd);
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
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, Windows desktop!");

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// Here your application is laid out.
		// For this introduction, we just print out "Hello, Windows desktop!"
		// in the top left corner.
		TextOut(hdc,
			5, 5,
			greeting, _tcslen(greeting));
		// End application specific layout section.

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}