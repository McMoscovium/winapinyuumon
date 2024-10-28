#include "Window.h"


//�R���X�g���N�^
Window::Window(HINSTANCE hInstance, int nCmdShow) :hInstance(hInstance) {
	RegisterClass();
	Create();
	Show();
}

//�f�X�g���N�^
Window::~Window() {
	DestroyWindow(hwnd);//�E�B���h�E�̔j��
}

//�E�B���h�E�N���X�̓o�^
void Window::RegisterClass() {
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;//�E�B���h�E�v���V�[�W���̐ݒ�
	wc.hInstance = hInstance;
	wc.lpszClassName = className;
	::RegisterClass(&wc);//�E�B���h�E�N���X�̓o�^
}

//�E�B���h�E�쐬
void Window::Create() {
	hwnd = CreateWindowEx(
		0, className, L"Sample Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL
	);
}

//�E�B���h�E��\��
void Window::Show() {
	ShowWindow(hwnd, SW_SHOW);
}

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);//�A�v���I��
		return 0;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			/*
			�����ɕ`�揈����ǉ�
			*/

			EndPaint(hwnd, &ps);
		}
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);//�f�t�H���g�̏������Ăяo��
}