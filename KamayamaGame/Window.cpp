#include "Window.h"
#include "Game.h"
#include "GameState.h"
#include <Windows.h>
#include "GameObject.h"




//コンストラクタ
Window::Window(HINSTANCE hInstance, int nCmdShow, Game* game) :hInstance(hInstance), msg({}) {
	registerClass();
	create(game);
	registerUserData(game);
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
void Window::create(Game* game) {
	hwnd = CreateWindowEx(
		0, className, L"Sample Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, hInstance, NULL
	);
}

void Window::registerUserData(Game* game)
{
	UserData* userData = new UserData(game, this);
	SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)userData);
}

void Window::getClientRect(RECT* rect) const
{
	GetClientRect(hwnd, rect);
}


void Window::renderGameObject(const GameObject* gameObject,HDC hdc)const
{
	HDC hdcMem = CreateCompatibleDC(hdc);//スプライトシートに紐付けるHDC
	HBITMAP oldMemBitmap = (HBITMAP)SelectObject(hdcMem, gameObject->getSpriteImage());
	//透過色を考慮してHDCの選択するデバイスに描画
	TransparentBlt(hdc,
		gameObject->getPositionX(), gameObject->getPositionY(),
		gameObject->getWidth(), gameObject->getHeight(),
		hdcMem,
		gameObject->originOfCurrentFrame(), 0,
		gameObject->getWidth(), gameObject->getHeight(),
		RGB(255, 0, 255));
	SelectObject(hdcMem, oldMemBitmap);
	DeleteDC(hdcMem);//HDC解放
}

//ウィンドウを表示
void Window::show() const{
	ShowWindow(hwnd, SW_SHOW);
}

void Window::render(const GameState* currentState)
{
	//HDC達を確保する
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);//ウィンドウのデバイスコンテキスト

	HDC hdcBackBuffer = CreateCompatibleDC(hdc);// バックバッファ用デバイスコンテキスト
	HBITMAP hBackBuffer = CreateCompatibleBitmap(hdc, width, height);//バックバッファ用ビットマップ
	
	HBITMAP oldhBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBackBuffer);//バックバッファ用HDCはバックバッファ用ビットマップを選択する。oldBitmapにもともバックバッファ用HDCが選択していたオブジェクトを格納しておく（オブジェクトリークの防止のため）

	
	std::vector<std::string> objectOrder = currentState->getObjectOrder();//画面奥から順に描画するので、その順序を取得

	//ゲームオブジェクトを奥から順にバックバッファに描画する
	for (int i = 0; i < currentState->numberOfObjects(); i++) {
		//i番目のオブジェクトを描画
		const GameObject* drawnObject = currentState->getGameObject(objectOrder.at(i));
		renderGameObject(drawnObject,hdcBackBuffer);
	}
	//出来上がったバックバッファを本来のデバイスコンテキストに描画
	RECT clientRect;
	getClientRect(&clientRect);
	BitBlt(hdc, 0, 0, clientRect.right, clientRect.bottom, hdcBackBuffer, 0, 0, SRCCOPY);//描画

	//HDC達を解放する
	SelectObject(hdcBackBuffer, oldhBitmap);
	DeleteObject(hBackBuffer);
	DeleteDC(hdcBackBuffer);

	EndPaint(hwnd, &ps);//このときにhdc解放される
}

HDC Window::getDC() const
{
	return ::GetDC(hwnd);
}

bool Window::update(Game* game)
{
	if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) {//msgにメッセージを格納
		TranslateMessage(&msg);
		DispatchMessageW(&msg);//ウィンドウプロシージャを実行
	}
	if (msg.message == WM_DESTROY) {
		return 0;
	}
	return 1;
}


//ウィンドウに渡すユーザー定義の構造体。ウィンドウプロシージャ内で外部のデータを使う時に使う


//ウィンドウプロシージャ
LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);//アプリ終了
		return 0;
	case WM_PAINT:
		UserData* userData = (UserData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		Game* game = userData->game;
		Window* window = userData->window;
		window->render(game->getCurrentState());
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);//デフォルトの処理を呼び出す
}