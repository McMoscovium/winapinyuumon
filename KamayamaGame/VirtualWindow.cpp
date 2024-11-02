#include "VirtualWindow.h"
#include<Windows.h>
#include"Window.h"

VirtualWindow::VirtualWindow(Window* window) :hdcBackBuffer(nullptr), hBackBuffer(nullptr)
{
	HDC hdc = window->getDC();
	hdcBackBuffer = CreateCompatibleDC(hdc);
	hBackBuffer = CreateCompatibleBitmap(hdc, window->width, window->height);
	SelectObject(hdcBackBuffer, hBackBuffer);
}

VirtualWindow::~VirtualWindow()
{
}
