#pragma once
#include<Windows.h>

class GameState;
class Game;
class GameObject;
class Window;
class InputManager;

struct UserData {
public:
	Game* game;
	Window* window;
	InputManager* inputManager;
	UserData(Game* game, Window* window, InputManager* inputManager) :game(game), window(window), inputManager(inputManager) {}
};


class Window
{
public:
	const int width = 1152;
	const int height = 720;


	//コンストラクタ。ウィンドウクラスの登録、ウィンドウの作成まで行う。
	Window(HINSTANCE hInstance, int nCmdShow, Game* game, InputManager* inputManager);
	~Window();

	//現在のウィンドウを表示
	void show() const;

	//Gameクラスの情報に従いウィンドウを描画しなおす。
	void render(const GameState* currentState);

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
	void create(Game* game);
	//ウィンドウプロシージャに渡すインスタンスを登録
	void registerUserData(Game* game, InputManager* inputManager);
	//クライアント領域の四角形の寸法（ピクセル）を取得
	//左上隅の座標が(0,0)となる
	void getClientRect(RECT* rect)const;
	//渡されたゲームオブジェクトをHDCの選択するデバイスに描画（透過色を考慮）
	void renderGameObject(const GameObject* gameObject, HDC hdc)const;
	
};