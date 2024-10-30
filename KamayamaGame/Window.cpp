#include "Window.h"
#include<Windows.h>


//コンストラクタ
Window::Window(HINSTANCE hInstance, int nCmdShow) :hInstance(hInstance) {
	registerClass();
	create();
}

//デストラクタ
Window::~Window() {
	DestroyWindow(hwnd);//ウィンドウの破棄
}

//ウィンドウクラスの登録
void Window::registerClass() {
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;//ウィンドウプロシージャの設定
	wc.hInstance = hInstance;
	wc.lpszClassName = className;
	::RegisterClass(&wc);//ウィンドウクラスの登録
}

//ウィンドウ作成。
void Window::create() {
	hwnd = CreateWindowEx(
		0, className, L"Sample Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, hInstance, NULL
	);
}

//ウィンドウを表示
void Window::show() const{
	ShowWindow(hwnd, SW_SHOW);
}

void Window::render(Game*)
{
}


HDC Window::getDC() const
{
	return ::GetDC(hwnd);
}

//ウィンドウプロシージャ
LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);//アプリ終了
		return 0;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			/*
			ここに描画処理を追加
			*/

			EndPaint(hwnd, &ps);
		}
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);//デフォルトの処理を呼び出す
}