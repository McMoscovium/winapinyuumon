#pragma once

/*
PC内部でのゲームの進行を管理するクラス。
仮想画面への描画も行う。
*/
#include "unordered_map"

class GameState;
class VirtualWindow;
class Window;
class InputManager;
class ObjectName;

class Game
{
private:
	GameState* currentState;

	void drawWindow();//仮想画面にゲーム画面を描画する

	
public:
	Game();
	~Game();

	void update(InputManager* inputManager);//ゲーム状態ごとに設定された更新処理を行う
	void changeState(GameState* newState);//currentStateを変更する
	void setBackBuffer(Window* window);//virtualWindowの初期設定
	const GameState* getCurrentState()const;
	//終了処理
	void termination();
};