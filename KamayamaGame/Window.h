#pragma once
#include<Windows.h>

class GameState;
class Game;

class Window
{
public:
	const int width = 800;
	const int height = 600;


	//コンストラクタ。ウィンドウクラスの登録、ウィンドウの作成まで行う。
	Window(HINSTANCE hInstance, int nCmdShow);
	~Window();

	//現在のウィンドウを表示
	void show() const;

	//Gameクラスの情報に従いウィンドウを描画しなおす。
	void render(const Game*);

	//ウィンドウハンドルを取得
	HWND getHandle()const { return hwnd; }

	//デバイスコンテキストを取得
	HDC getDC()const;

	bool defaultUpdate();//毎メッセージループで行う処理（WM_DESTROY等の処理）

protected:
	//ウィンドウプロシージャ
	static LRESULT CALLBACK WindowProc(HWND, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
private:
	HINSTANCE hInstance;
	HWND hwnd;
	const wchar_t* className = L"SampleWindowClass";
	MSG msg;
	

	//ウィンドウクラスの登録
	void registerClass();
	//ウィンドウ作成。今後、パラメータ類の変更も可能な実装に変える
	void create();
};

