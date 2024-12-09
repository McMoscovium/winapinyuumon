#pragma once

/*
PC内部でのゲームの進行を管理するクラス。
仮想画面への描画も行う。
*/
#include "unordered_map"
#include "IGameState.h"
#include "Camera.h"

class Window;
class InputManager;

class Game
{
private:
	IGameState* currentState = nullptr;
	InputManager& inputManager;
	Window* window;
	Camera camera;
	int money = 0;
	const HINSTANCE& hInstance;//アプリケーションのインスタンスはンドル。リソースを使うのにいる。

	
public:
	Game(InputManager& inputManager, const HINSTANCE& hInstance);
	~Game();


	//
	bool registerWindow(Window* window);
	void update();//ゲーム状態ごとに設定された更新処理を行う
	void changeState(IGameState* newState);//currentStateを変更する
	//
	IGameState* getCurrentState()const;
	//
	InputManager& getInputManager() {
		return inputManager;
	}
	//
	Window* getWindow() {
		return window;
	}
	const HINSTANCE& getHInstance();
};