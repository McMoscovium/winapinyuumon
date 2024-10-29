#pragma once

/*
PC内部でのゲームの進行を管理するクラス。
仮想画面への描画も行う。
*/


class GameState;
class VirtualWindow;
class Window;

class Game
{
private:
	GameState* currentState;
	VirtualWindow* virtualWindow;

	void drawWindow();//仮想画面にゲーム画面を描画する
	
public:
	Game();
	Game(Window* window);//ウィンドウありきのコンストラクタ。仮想ウィンドウの設定を行う。
	~Game();

	void update();//ゲーム状態ごとに設定された更新処理を行う
	void changeState(GameState* newState);//状態を変更する
	void setBackBuffer(Window* window);//virtualWindowの初期設定
};