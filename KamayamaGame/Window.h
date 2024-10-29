#pragma once
#include<Windows.h>

class Game;

class Window
{
public:
	const int width = 800;
	const int height = 600;


	//コンストラクタ。ウィンドウクラスの登録、ウィンドウの作成、ウィンドウの表示まで行う。
	Window(HINSTANCE hInstance, int nCmdShow);
	~Window();

	void show();

	//ウィンドウハンドルを取得
	HWND getHandle()const { return hwnd; }

	//デバイスコンテキストを取得
	HDC getDC()const;

protected:
	//ウィンドウプロシージャ
	static LRESULT CALLBACK WindowProc(HWND, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
private:
	HINSTANCE hInstance;
	HWND hwnd;
	const wchar_t* className = L"SampleWindowClass";
	

	//ウィンドウクラスの登録
	void registerClass();
	//ウィンドウ作成。今後、パラメータ類の変更も可能な実装に変える
	void create();
	
};

