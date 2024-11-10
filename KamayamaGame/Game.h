#pragma once

/*
PC内部でのゲームの進行を管理するクラス。
仮想画面への描画も行う。
*/
#include "unordered_map"
#include "IGameState.h"

class Window;
class InputManager;

class Game
{
private:
	IGameState* currentState = nullptr;
	InputManager& inputManager;
	Window* window;

	
public:
	Game(InputManager& inputManager);
	~Game();


	//
	bool registerWindow(Window* window);
	void update();//ゲーム状態ごとに設定された更新処理を行う
	void changeState(IGameState* newState);//currentStateを変更する
	//
	const IGameState* getCurrentState()const;
	//
	InputManager& getInputManager() {
		return inputManager;
	}
	//
	Window* getWindow() {
		return window;
	}
};