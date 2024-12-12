#include "Game/Window.h"
#include "Game/Game.h"
#include "GameState/GameState.h"
#include <Windows.h>
#include "GameObject/GameObject.h"
#include <iostream>
#include "Game/InputManager.h"
#include "resource.h"



//コンストラクタ
Window::Window(HINSTANCE hInstance, int nCmdShow, InputManager* inputManager,Game& game) :
	hInstance(hInstance), 
	msg({})
{
	//ウィンドウ作成
	registerClass();
	create(game);
	registerUserData(&game);
}

//デストラクタ
Window::~Window() {
	DestroyWindow(hwnd);//ウィンドウの破棄
}

RECT Window::getClientRect()
{
	RECT rect;
	GetClientRect(hwnd, &rect);
	return rect;
}

//ウィンドウクラスの登録
void Window::registerClass() {
	WNDCLASSEX wc = {};
	wc.lpfnWndProc = WindowProc;//ウィンドウプロシージャの設定
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
	wc.lpszClassName = className;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(100, 100, 100));  // 黒色で塗りつぶし
	wc.lpszMenuName = NULL;
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
	::RegisterClassExW(&wc);//ウィンドウクラスの登録
}

//ウィンドウ作成。
void Window::create(Game& game) {
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	RECT rect = { 0, 0, width, height };//クライアント領域
	AdjustWindowRect(&rect, dwStyle, FALSE); // FALSEはメニューバーがない場合

	int windowWidth = rect.right - rect.left;
	int windowHeight = rect.bottom - rect.top;

	hwnd = CreateWindowEx(
		0,
		className,
		L"クマの釜山のホームランダービー！",
		dwStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowWidth, windowHeight,
		NULL,
		NULL,
		hInstance,
		NULL
	);
}

void Window::registerUserData(Game* game)
{
	userData = new UserData(game);
	SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)userData);
}

RECT Window::getClientRect() const
{
	RECT rect;
	if (GetClientRect(hwnd, &rect)) {
		return rect;
	}
	return { 0,0,0,0 };
}




bool Window::getClientRect(RECT* rect)const
{
	if (GetClientRect(hwnd, rect)) {
		return true;
	}
	return false;
}

//ウィンドウを表示
void Window::show() const{
	ShowWindow(hwnd, SW_SHOW);
}

void Window::render(const GameObjectManager& gameObjectManager)
{
	//HDC達を確保する
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);//ウィンドウのデバイスコンテキスト

	HDC hdcBackBuffer = CreateCompatibleDC(hdc);// バックバッファ用デバイスコンテキスト
	HBITMAP hBackBuffer = CreateCompatibleBitmap(hdc, width, height);//バックバッファ用ビットマップ
	
	HBITMAP oldhBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBackBuffer);//バックバッファ用HDCはバックバッファ用ビットマップを選択する。oldBitmapにもともバックバッファ用HDCが選択していたオブジェクトを格納しておく（オブジェクトリークの防止のため）


	// バックバッファを薄い灰色で塗りつぶす
	HBRUSH hBrush = CreateSolidBrush(RGB(100, 100, 100)); // 薄い灰色 (RGB)
	RECT rect;
	GetClientRect(hwnd, &rect);
	FillRect(hdcBackBuffer, &rect, hBrush);  // バックバッファに塗りつぶし
	DeleteObject(hBrush);  // ブラシを解放
	
	std::vector<std::reference_wrapper<GameObject>> objectOrder = gameObjectManager.getDrawOrder();//画面奥から順に描画するので、その順序を取得

	//ゲームオブジェクトを奥から順にバックバッファに描画する
	for (auto& object : objectOrder) {
		//i番目のオブジェクトを選択
		//visible=falseなら次のオブジェクトへ]
		GameObject& obj = object.get();
		if (!(obj.isVisible())) {
			continue;
		}
		obj.render(hdcBackBuffer);
	}
	//出来上がったバックバッファを本来のデバイスコンテキストに描画
	if (
		BitBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hdcBackBuffer, 0, 0, SRCCOPY)
		) {
		//描画成功
	}
	else {
		OutputDebugString(L"仮想画面を描画失敗\n");
	}

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

UINT Window::getFps() const
{
	return fps;
}

bool Window::update(Game* game)
{
	//メッセージがなくなるまでメッセージを処理
	if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {//msgにメッセージを格納
		if (msg.message == WM_QUIT) {
			return false;//ループ終了
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);//ウィンドウプロシージャを実行
	}	
	return true;//ループ続行
}

//ウィンドウプロシージャ
LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CREATE: {
		break;
	}
	case WM_CLOSE://×ボタンが押された
		DestroyWindow(hwnd);
		return 0;
	case WM_DESTROY://ウィンドウ破棄メッセージを受信
		PostQuitMessage(0);//メッセージループ終了
		break;
	case WM_PAINT: {
		UserData* userData = (UserData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		Game* game = userData->game;
		Window* window = game->getWindow();
		window->render(game->getCurrentState()->getGameObjectManager());
		return 0;
	}
	case WM_MOUSEMOVE: {
		// マウスの座標をクライアント領域基準で取得
		int mouseX = LOWORD(lParam);  // マウスのX座標
		int mouseY = HIWORD(lParam);  // マウスのY座標

		//InputManagerを更新
		UserData* userData = (UserData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		InputManager& inputManager = userData->game->getInputManager();
		POINT cursor = { LOWORD(lParam),HIWORD(lParam) };
		inputManager.setCursorPosition(cursor);
		return 0;
	}
	case WM_LBUTTONDOWN: {
		UserData* userData = (UserData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		//inputManagerを更新
		InputManager& inputManager = userData->game->getInputManager();
		inputManager.setKeyState(VK_LBUTTON, InputManager::KeyState::KEY_PRESSED);
		return 0;
	}
	case WM_LBUTTONUP: {
		UserData* userData = (UserData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		//inputManagerを更新
		InputManager& inputManager = userData->game->getInputManager();
		inputManager.setKeyState(VK_LBUTTON, InputManager::KeyState::KEY_RELEASED);
		return 0;
	}
	case WM_KEYDOWN: {
		UserData* userData = (UserData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		//inputManagerを更新
		InputManager& inputManager = userData->game->getInputManager();
		if (wParam == 0x4D) {
			inputManager.setKeyState(0x4D, InputManager::KeyState::KEY_PRESSED);
		}
		return 0;
	}
	case WM_KEYUP: {
		UserData* userData = (UserData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		//inputManagerを更新
		InputManager& inputManager = userData->game->getInputManager();
		if (wParam == 0x4D) {
			inputManager.setKeyState(0x4D, InputManager::KeyState::KEY_RELEASED);
		}
		return 0;
	}
	case WM_ERASEBKGND:
		return 1; // 背景を消去しない
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);//デフォルトの処理を呼び出す
}

void Window::termination()
{
	delete userData;
}
