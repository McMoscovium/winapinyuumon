#pragma once
#include<Windows.h>

class IGameState;
class Game;
class GameObject;
class InputManager;
class GameObjectManager;

struct UserData {
public:
	Game* game;
	UserData(Game* game) :game(game) {}
};


class Window
{
public:
	const int width = 1152;
	const int height = 720;


	//コンストラクタ。ウィンドウクラスの登録、ウィンドウの作成まで行う。
	Window(HINSTANCE hInstance, int nCmdShow, InputManager* inputManager, Game& game);
	~Window();

	//
	RECT getClientRect();


	//現在のウィンドウを表示
	void show() const;

	//Gameクラスの情報に従いウィンドウを描画しなおす。
	void render(const GameObjectManager& gameObjectManager)const;

	//ウィンドウハンドルを取得
	HWND getHandle()const { return hwnd; }

	//デバイスコンテキストを取得
	HDC getDC()const;

	UINT getFps()const;

	bool update(Game* game);//毎メッセージループで行う処理（WM_DESTROY等の処理）

	//ウィンドウプロシージャ
	static LRESULT CALLBACK WindowProc(HWND, UINT uMsg, WPARAM wParam, LPARAM lParam);

	//終了処理
	void termination();
	//左上隅の座標が(0,0)となる
	RECT getClientRect()const;

	//
	bool isInClientRect(POINT point)const {
		RECT rect = getClientRect();
		if (point.x <= rect.right &&
			point.x >= rect.left &&
			point.y <= rect.bottom &&
			point.y >= rect.top
			) {
			return true;
		}
		else {
			return false;
		}
	}

protected:
	
	
private:
	HINSTANCE hInstance;
	HWND hwnd;
	const wchar_t* className = L"SampleWindowClass";
	MSG msg;
	UINT fps = 30;
	UserData* userData = nullptr;

	//ウィンドウクラスの登録
	void registerClass();
	//ウィンドウ作成。今後、パラメータ類の変更も可能な実装に変える。
	void create(Game& game);
	//ウィンドウプロシージャに渡すインスタンスを登録
	void registerUserData(Game* game);
	//クライアント領域の四角形の寸法（ピクセル）を取得
	

	bool getClientRect(RECT* rect)const;
	
};