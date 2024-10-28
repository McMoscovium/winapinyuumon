#pragma once
#include<Windows.h>

class Window
{
public:
	Window(HINSTANCE hInstance, int nCmdShow);
	~Window();

	void Show();

	//�E�B���h�E�n���h�����擾
	HWND GetHandle()const { return hwnd; }

protected:
	//�E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK WindowProc(HWND, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE hInstance;
	HWND hwnd;
	const wchar_t* className = L"SampleWindowClass";

	void RegisterClass();
	void Create();
};

