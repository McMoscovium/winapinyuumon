#include<Windows.h>
#include<Vfw.h>
#include<windowsx.h>
#include"resource.h"
#include"game.h"
#include<iostream>
#include<sstream>
#include<string>
//#pragma comment(lib,"msimg32.lib")



static HBITMAP
	hTitlePicture,
	hStartButton,
	hStartButtonPointed,
	hStatusButton,
	hStatusButtonPointed,
	hGachaButton,
	hGachaButtonPointed,
	hQuitButton,
	hQuitButtonPointed,
	hBusan,
	hFieldPicture,
	hHitterBusan;
static HBITMAP
hBitmapWindow;
//おされているボタンの種類．phaseによって変わる
static int PointedButton = -1;

const POSITION TitleBusanPicturePos = { 32,48 };
const POSITION TitleStartButtonPos = { 240,352 };
const POSITION TitleStatusButtonPos = { 576,352 };
const POSITION TitleGachaButtonPos = { 240,528 };
const POSITION TitleQuitButtonPos = { 576,528 };
static std::string phase = "title";

//ウィンドウプロシージャ関数の宣言
LRESULT CALLBACK TitleWndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
LRESULT CALLBACK GameWndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

//その他関数の宣言
bool IsCursorOnRect(POSITION ButtonPosition, SIZE ButtonSize, int CursorX, int CursorY);
SIZE GetBitmapSize(HBITMAP hBitmap);
void DrawIntWithDrawTextExW(HDC hdc, int value, int x, int y);

//グローバル変数
static int X, Y;
static SIZE TitleBusanSize, TitleButtonSize, HitterBusanSize;


int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInst,
	LPSTR lpszCmdLine,
	int nCmdShow) {

	const TCHAR CLASSNAME[] = L"クマの釜山のホームランダービー！";

	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wc.lpfnWndProc = TitleWndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = (HICON)LoadImage(
		NULL, L"..\\resources\\アイコン.ico",
		IMAGE_ICON, NULL, NULL,
		LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wc.hCursor = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = CLASSNAME;
	wc.hIconSm = (HICON)LoadImage(
		NULL, L"..\\resources\\システムアイコン.ico",
		IMAGE_ICON, NULL, NULL,
		LR_DEFAULTSIZE | LR_LOADFROMFILE);

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, L"RegisterClassEx関数　失敗", L"", MB_OK);
		return 0;
	}

	StateInfo* pState = new (std::nothrow) StateInfo;

	if (pState == NULL) {
		return 0;
	}

	HWND hWnd = CreateWindowEx(
		WS_EX_ACCEPTFILES | WS_EX_CONTROLPARENT,
		CLASSNAME,
		CLASSNAME,
		//ウィンドウスタイルオプション
		WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
		//サイズ
		0,
		0,
		1152,
		720,
		//親ウィンドウ
		NULL,
		//メニュー
		NULL,
		GetModuleHandle(NULL),
		//追加データ
		NULL
	);

	if (!hWnd) {
		MessageBox(NULL, L"CreateWindowEx関数　失敗", L"", MB_OK);
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	//変数準備
	static HDC hdc;
	static HDC hdcMem;
	//画像の読み込み，サイズの取得
	
	
	

	//矩形の座標を格納する構造体
	struct rect {
		int x;
		int y;
	};
	//カーソルの大きさの初期化
	static rect cursorSize = { 10,20 };

	//メッセ―ジキュー
	MSG msg;
	msg.message = NULL;

	//メッセージループ
	
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}


	//登録解除
	if (!UnregisterClassW(wc.lpszClassName, GetModuleHandle(NULL))) {
		MessageBoxW(NULL, L"登録解除失敗", L"err", MB_OK);
	}

	return 0;
}


//phaseが"title"のときのタイトルウィンドウプロシージャ
LRESULT CALLBACK TitleWndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	static HWND hMCI;
	static HDC hdc, hdcMem;
	hdc = GetDC(hWnd);
	static PAINTSTRUCT ps;

	
	//クライアント領域のデータ
	RECT rc;
	GetClientRect(hWnd, &rc);

	//おされているボタンの種類．phaseによって変わる
	static int PointedButton = -1;
	
	
	switch (msg){
	case WM_CREATE:
		hTitlePicture = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\タイトル画面.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		hStartButton = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\はじめる.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		::TitleButtonSize = GetBitmapSize(hStartButton);
		hStartButtonPointed = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\はじめるpointed.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		hStatusButton = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\ステータス.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		hStatusButtonPointed = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\ステータスpointed.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		hGachaButton = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\ガチャ.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		hGachaButtonPointed = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\ガチャpointed.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		hQuitButton = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\おわる.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		hQuitButtonPointed = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\おわるpointed.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		hBusan = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\クマの釜山.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		TitleBusanSize = GetBitmapSize(hBusan);
		hFieldPicture = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\フィールド.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		hHitterBusan = static_cast<HBITMAP>(LoadImageW(NULL, L"..\\resources\\打者.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		HitterBusanSize = GetBitmapSize(hHitterBusan);

		//音楽の再生
		if (hMCI = MCIWndCreate(hWnd, ((LPCREATESTRUCT)lp)->hInstance, WS_CHILD, L"..\\resources\\bgm1.wav")) {
			MCIWndPlay(hMCI);
		}
		else {
			MessageBox(hWnd, L"音楽再生失敗", L"", MB_OK);//@ERROR
		}
		
		break;
	
	case WM_MOUSEMOVE:
		X = LOWORD(lp);
		Y = HIWORD(lp);

		break;

	case WM_PAINT:
		PointedButton = -1;
		hdc = GetDC(hWnd);
		hdcMem = CreateCompatibleDC(hdc);
		
		//背景の描画
		SelectObject(hdcMem, hTitlePicture);
		BitBlt(hdc, 0, 0, rc.right, rc.bottom, hdcMem, 0, 0, SRCCOPY);
		//釜山の描画
		SelectObject(hdcMem, hBusan);
		TransparentBlt(hdc, TitleBusanPicturePos.x, TitleBusanPicturePos.y, TitleBusanSize.cx, TitleBusanSize.cy, hdcMem, 0, 0, TitleBusanSize.cx, TitleBusanSize.cy, RGB(0xFF, 0x00, 0xFF));
		SelectObject(hdcMem, hStartButton);
		TransparentBlt(hdc, TitleStartButtonPos.x, TitleStartButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
		SelectObject(hdcMem, hStatusButton);
		TransparentBlt(hdc, TitleStatusButtonPos.x, TitleStatusButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
		SelectObject(hdcMem, hGachaButton);
		TransparentBlt(hdc, TitleGachaButtonPos.x, TitleGachaButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
		SelectObject(hdcMem, hQuitButton);
		TransparentBlt(hdc, TitleQuitButtonPos.x, TitleQuitButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
		DeleteDC(hdcMem);
		DeleteDC(hdc);
		break;

	case WM_LBUTTONDOWN:
		X = LOWORD(lp);
		Y = HIWORD(lp);
		if (IsCursorOnRect(TitleStartButtonPos, TitleButtonSize, X, Y)) {
			//スタートボタンが押された
			PointedButton = 1;

			hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, hStartButtonPointed);
			TransparentBlt(hdc, TitleStartButtonPos.x, TitleStartButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
			DeleteDC(hdcMem);
			DeleteDC(hdc);
		}
		else if (IsCursorOnRect(TitleStatusButtonPos, TitleButtonSize, X, Y)) {
			//ステータスボタンが押された
			PointedButton = 2;
			hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, hStatusButtonPointed);
			TransparentBlt(hdc, TitleStatusButtonPos.x, TitleStatusButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
			DeleteDC(hdcMem);
			DeleteDC(hdc);
		}
		else if (IsCursorOnRect(TitleGachaButtonPos, TitleButtonSize, X, Y)) {
			//ガチャボタンが押された
			PointedButton = 3;
			hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, hGachaButtonPointed);
			TransparentBlt(hdc, TitleGachaButtonPos.x, TitleGachaButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
			DeleteDC(hdcMem);
			DeleteDC(hdc);
		}
		else if (IsCursorOnRect(TitleQuitButtonPos, TitleButtonSize, X, Y)) {
			//おわるボタンが押された
			PointedButton = 4;
			hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, hQuitButtonPointed);
			TransparentBlt(hdc, TitleQuitButtonPos.x, TitleQuitButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
			DeleteDC(hdcMem);
			DeleteDC(hdc);
		}
		break;

	case WM_LBUTTONUP:
		X = LOWORD(lp);
		Y = HIWORD(lp);
		if (PointedButton = 1 &&
			IsCursorOnRect(TitleStartButtonPos, TitleButtonSize, X, Y)) {
			//スタートボタンが押された状態で，スタートボタンの上で左ボタンが離された
			PointedButton = -1;
			phase = "game";
			SetWindowLongPtrW(hWnd, GWLP_WNDPROC, (LONG_PTR)GameWndProc);
			SendMessage(hWnd, WM_CREATE, 0, 0);
			SendMessage(hWnd, WM_PAINT, 0, 0);
		}
		else if (PointedButton = 2 &&
			IsCursorOnRect(TitleStatusButtonPos, TitleButtonSize, X, Y)) {
			//ステータスボタンが押された状態で，ステータスボタンの上で左ボタンが離された
			PointedButton = -1;
			hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, hStatusButton);
			TransparentBlt(hdc, TitleStatusButtonPos.x, TitleStatusButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
			DeleteDC(hdcMem);
			DeleteDC(hdc);
		}
		else if (PointedButton = 3 &&
			IsCursorOnRect(TitleGachaButtonPos, TitleButtonSize, X, Y)) {
			//ガチャボタンが押された状態で，ガチャボタンの上で左ボタンが離された
			PointedButton = -1;
			hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, hGachaButton);
			TransparentBlt(hdc, TitleGachaButtonPos.x, TitleGachaButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
			DeleteDC(hdcMem);
			DeleteDC(hdc);
		}
		else if (PointedButton = 4 &&
			IsCursorOnRect(TitleQuitButtonPos, TitleButtonSize, X, Y)) {
			//おわるボタンが押された状態で，おわるボタンの上で左ボタンが離された
			PointedButton = -1;

			SendMessage(hWnd, WM_CLOSE, NULL, NULL);

			hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, hQuitButton);
			TransparentBlt(hdc, TitleQuitButtonPos.x, TitleQuitButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
			DeleteDC(hdcMem);
			DeleteDC(hdc);
		}
		else {
			//押されたボタンのうえでボタンが離されなかった
			PointedButton = -1;
			hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, hStartButton);
			TransparentBlt(hdc, TitleStartButtonPos.x, TitleStartButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
			SelectObject(hdcMem, hStatusButton);
			TransparentBlt(hdc, TitleStatusButtonPos.x, TitleStatusButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
			SelectObject(hdcMem, hGachaButton);
			TransparentBlt(hdc, TitleGachaButtonPos.x, TitleGachaButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
			SelectObject(hdcMem, hQuitButton);
			TransparentBlt(hdc, TitleQuitButtonPos.x, TitleQuitButtonPos.y, TitleButtonSize.cx, TitleButtonSize.cy, hdcMem, 0, 0, TitleButtonSize.cx, TitleButtonSize.cy, RGB(0xFF, 0x00, 0xFF));
			DeleteDC(hdcMem);
			DeleteDC(hdc);
		}
		break;

	

	case WM_COMMAND:
		switch (wp)
		{
		case ID_END:
			SendMessage(hWnd, WM_CLOSE, NULL, NULL);
			return 0;
		default:
			break;
		}
		return 0;

	case WM_CLOSE:
		if (IDYES == MessageBoxW(hWnd, L"本当に閉じますか？", L"確認", MB_YESNO | MB_ICONQUESTION)) {
			//閉じる処理
			DestroyWindow(hWnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}
	
	return DefWindowProc(hWnd, msg, wp, lp);
}

//phaseが"game"のときのウィンドウプロシージャ
LRESULT CALLBACK GameWndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	static HDC hdc, hdcMem, hdcMemWindow;
	hdc = GetDC(hWnd);
	static PAINTSTRUCT ps;
	
	//クライアント領域のデータ
	RECT rc;
	GetClientRect(hWnd, &rc);

	switch (msg) {
	case WM_CREATE:
		hFieldPicture = static_cast<HBITMAP>(LoadImage(NULL, L"..\\resources\\フィールド.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		hHitterBusan = static_cast<HBITMAP>(LoadImageW(NULL, L"..\\resources\\打者.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		HitterBusanSize = GetBitmapSize(hHitterBusan);
		break;

	case WM_MOUSEMOVE:
		X = LOWORD(lp);
		Y = HIWORD(lp);
		//メモリデバイスコンテキストの取得
		hdcMem = CreateCompatibleDC(hdc);
		hdcMemWindow = CreateCompatibleDC(hdc);
		//仮想ウィンドウを作成
		hBitmapWindow = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		//仮想ウィンドウを選択
		SelectObject(hdcMemWindow, hBitmapWindow);
		//フィールドの描画
		SelectObject(hdcMem, hFieldPicture);
		BitBlt(hdcMemWindow, 0, 0, rc.right, rc.bottom, hdcMem, 0, 0, SRCCOPY);
		SelectObject(hdcMem, hHitterBusan);
		TransparentBlt(hdcMemWindow, X - HitterBusanSize.cx, Y - HitterBusanSize.cy / 2, HitterBusanSize.cx, HitterBusanSize.cy, hdcMem, 0, 0, HitterBusanSize.cx, HitterBusanSize.cy, RGB(0xFF, 0x00, 0xFF));

		//一括で描画
		BitBlt(hdc, 0, 0, rc.right, rc.bottom, hdcMemWindow, 0, 0, SRCCOPY);
		DeleteObject(hBitmapWindow);
		DeleteDC(hdcMemWindow);
		DeleteDC(hdcMem);
		DeleteDC(hdc);
		break;

	case WM_PAINT:
	{
		//メモリデバイスコンテキストの取得
		hdcMem = CreateCompatibleDC(hdc);
		hdcMemWindow = CreateCompatibleDC(hdc);
		//仮想ウィンドウを作成
		hBitmapWindow = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		//仮想ウィンドウを選択
		SelectObject(hdcMemWindow, hBitmapWindow);
		//フィールドの描画
		SelectObject(hdcMem, hFieldPicture);
		BitBlt(hdcMemWindow, 0, 0, rc.right, rc.bottom, hdcMem, 0, 0, SRCCOPY);
		SelectObject(hdcMem, hHitterBusan);
		TransparentBlt(hdcMemWindow, X - HitterBusanSize.cx, Y - HitterBusanSize.cy / 2, HitterBusanSize.cx, HitterBusanSize.cy, hdcMem, 0, 0, HitterBusanSize.cx, HitterBusanSize.cy, RGB(0xFF, 0x00, 0xFF));

		//一括で描画
		BitBlt(hdc, 0, 0, rc.right, rc.bottom, hdcMemWindow, 0, 0, SRCCOPY);
		DeleteObject(hBitmapWindow);
		DeleteDC(hdcMemWindow);
		DeleteDC(hdcMem);
		DeleteDC(hdc);
		break;
	}
	case WM_LBUTTONDOWN:
		
		break;

	case WM_LBUTTONUP:
		
		break;


	case WM_CLOSE:
		if (IDYES == MessageBoxW(hWnd, L"本当に閉じますか？", L"確認", MB_YESNO | MB_ICONQUESTION)) {
			//閉じる処理
			DestroyWindow(hWnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wp, lp);
}



bool IsCursorOnRect(POSITION ButtonPosition, SIZE ButtonSize, int CursorX, int CursorY) {
	/*
	カーソルの座標が長方形に入っているか判別する関数
	rx:長方形のx座標
	ry:長方形のy座標
	sx:長方形の幅
	sy:長方形の高さ
	cx:カーソルのx座標
	cy:カーソルのy座標
	*/
    int rx = ButtonPosition.x;
    int ry = ButtonPosition.y;
    int sx = ButtonSize.cx;
    int sy = ButtonSize.cy;
    int cx = CursorX;
    int cy = CursorY;

	if (rx <= cx && cx <= rx + sx &&
		ry <= cy && cy <= ry + sy) {
		return true;
	}
	else {
		return false;
	}
}

SIZE GetBitmapSize(HBITMAP hBitmap)
{
	BITMAP bmp;
	SIZE size = { 0 };

	if (GetObject(hBitmap, sizeof(BITMAP), &bmp))
	{
		size.cx = bmp.bmWidth;
		size.cy = bmp.bmHeight;
	}

	return size;
}

void DrawIntWithDrawTextExW(HDC hdc, int value, int x, int y)
{
	// int型を文字列に変換
	std::wstring text;
	text = std::to_wstring(value); // int型をwstring型に変換

	// DrawTextExWを使ってテキストを描画
	RECT rc = { x, y, 0, 0 }; // 描画領域の左上座標(x, y)
	DrawTextExW(hdc, const_cast<LPWSTR>(text.c_str()), -1, &rc, DT_LEFT, nullptr);
}