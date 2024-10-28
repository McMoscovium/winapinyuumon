#pragma once
#include<Windows.h>

class Window
{
public:
	Window(HINSTANCE hInstance, int nCmdShow);
	~Window();

	void Show();

	//ウィンドウハンドルを取得
	HWND GetHandle()const { return hwnd; }

protected:
	//ウィンドウプロシージャ
	static LRESULT CALLBACK WindowProc(HWND, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE hInstance;
	HWND hwnd;
	const wchar_t* className = L"SampleWindowClass";

	void RegisterClass();
	void Create();
};

