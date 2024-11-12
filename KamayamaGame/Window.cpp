#include "Window.h"
#include "Game.h"
#include "GameState.h"
#include <Windows.h>
#include "GameObject.h"
#include <iostream>
#include "InputManager.h"

const UINT fps = 60;


//コンストラクタ
Window::Window(HINSTANCE hInstance, int nCmdShow, InputManager* inputManager,Game& game) :hInstance(hInstance), msg({}) {
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
	wc.hIcon = (HICON)LoadImage(
		NULL, L".\\assets\\アイコン.ico",
		IMAGE_ICON, NULL, NULL,
		LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wc.hCursor = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));  // 黒色で塗りつぶし
	wc.lpszMenuName = NULL;
	wc.hIconSm = (HICON)LoadImage(
		NULL, L".\\assets\\システムアイコン.ico",
		IMAGE_ICON, NULL, NULL,
		LR_DEFAULTSIZE | LR_LOADFROMFILE);
	::RegisterClassExW(&wc);//ウィンドウクラスの登録
}

//ウィンドウ作成。
void Window::create(Game& game) {
	hwnd = CreateWindowEx(
		0,
		className,
		L"Sample Window",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width, height,
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


void Window::renderGameObject(const GameObject& gameObject,HDC hdc)const
{
	HDC hdcMem = CreateCompatibleDC(hdc);//スプライトシートに紐付けるHDC
	HBITMAP oldMemBitmap = (HBITMAP)SelectObject(hdcMem, gameObject.getSpriteImage());
	//透過色を考慮してHDCの選択するデバイスに描画
	if (TransparentBlt(
		hdc,
		gameObject.getPositionX(),
		gameObject.getPositionY(),
		gameObject.getWidthOnWindow(),
		gameObject.getHeightOnWindow(),
		hdcMem,
		gameObject.originOfCurrentFrame(),
		0,
		gameObject.getWidth(),
		gameObject.getHeight(),
		RGB(255, 0, 255))
		) {
		//描画せいこう
	}
	else {
		//描画失敗
		OutputDebugString(L"仮想画面に描画失敗\n");
	}
	SelectObject(hdcMem, oldMemBitmap);
	DeleteDC(hdcMem);//HDC解放
}

bool Window::getClientRect(RECT* rect)
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

void Window::render(const IGameState* currentState)
{
	if (currentState == nullptr) {
		return;
	}
	//HDC達を確保する
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);//ウィンドウのデバイスコンテキスト

	HDC hdcBackBuffer = CreateCompatibleDC(hdc);// バックバッファ用デバイスコンテキスト
	HBITMAP hBackBuffer = CreateCompatibleBitmap(hdc, width, height);//バックバッファ用ビットマップ
	
	HBITMAP oldhBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBackBuffer);//バックバッファ用HDCはバックバッファ用ビットマップを選択する。oldBitmapにもともバックバッファ用HDCが選択していたオブジェクトを格納しておく（オブジェクトリークの防止のため）

		
	std::vector<std::wstring> objectOrder = currentState->getObjectOrder();//画面奥から順に描画するので、その順序を取得

	//ゲームオブジェクトを奥から順にバックバッファに描画する
	for (int i = 0; i < currentState->numberOfObjects(); i++) {
		//i番目のオブジェクトを選択
		const GameObject& drawnObject = currentState->getConstGameObject(objectOrder.at(i));
		//visible=falseなら次のオブジェクトへ
		if (!drawnObject.isVisible()) {
			continue;
		}
		renderGameObject(drawnObject,hdcBackBuffer);
	}
	//出来上がったバックバッファを本来のデバイスコンテキストに描画
	RECT clientRect;
	getClientRect(&clientRect);
	if (BitBlt(hdc, 0, 0, clientRect.right, clientRect.bottom, hdcBackBuffer, 0, 0, SRCCOPY)) {
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
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {//msgにメッセージを格納
		if (msg.message == WM_QUIT) {
			return false;//ループ終了
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);//ウィンドウプロシージャを実行
		return true;
	}
	else {//メッセージがない場合
		return true;//ループ続行
	}
}

//ウィンドウプロシージャ
LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CREATE: {
		SetTimer(hwnd, 1, 1000 / ::fps, NULL);
		break;
	}
	case WM_CLOSE://×ボタンが押された
		DestroyWindow(hwnd);
		return 0;
	case WM_DESTROY://ウィンドウ破棄メッセージを受信
		PostQuitMessage(0);//メッセージループ終了
		break;
	case WM_TIMER: {
		UserData* userData = (UserData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		Game* game = userData->game;
		InputManager& inputManager = game->getInputManager();
		inputManager.update();
		game->update();

		InvalidateRect(hwnd, NULL, FALSE);  //ウィンドウ全体を無効化し、システムにWM_PAINTをポストさせる
		return 0;
	}
	case WM_PAINT: {
		UserData* userData = (UserData*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		Game* game = userData->game;
		Window* window = game->getWindow();
		window->render(game->getCurrentState());
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

		// マウス座標をウィンドウのタイトルに表示
		std::wstring title = L"Mouse Position: (" + std::to_wstring(mouseX) + L", " + std::to_wstring(mouseY) + L")";
		SetWindowTextW(hwnd, title.c_str());
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
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);//デフォルトの処理を呼び出す
}

void Window::termination()
{
	delete userData;
}
