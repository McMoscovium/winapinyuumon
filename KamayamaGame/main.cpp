#include <Windows.h>
#include "Window.h"
#include "Game.h"
#include "InputManager.h"

//開発用
#include <iostream>

const LPCWSTR gameName = L"クマの釜山のホームランダービー！";


void mainLoop(Game* game,Window* window,InputManager* inputManager);
void termination();

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInst,
	LPSTR lpszCmdLine,
	int nShowCmd) {


	//初期化パート
	//必要なインスタンスを作成、初期化
	Game game;
	InputManager inputManager;
	Window window(hInstance, nShowCmd, &game, &inputManager);
	

	//初期画面レンダリング
	window.render(game.getCurrentState());
	//初期画面表示
	window.show();
	mainLoop(&game, &window, &inputManager);

	//終了処理
	//WM_QUITメッセージがもう出されているので、はやく終わる。
	termination();

	return 0;
}

void mainLoop(Game* game,Window* window, InputManager* inputManager) {
	while (window->update(game)) {// WM_QUITメッセージが受信されたらループを終了
	}
	//WM_QUITを受け取るとループを抜ける
}

void termination() {//メモリ解放処理等
	
}