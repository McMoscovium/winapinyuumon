#include <Windows.h>
#include "Window.h"
#include "Game.h"
#include "InputManager.h"
#include "TitleScreenState.h"


//開発用
#include <iostream>

const LPCWSTR gameName = L"クマの釜山のホームランダービー！";


void mainLoop(Game* game,Window* window);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInst,
	LPSTR lpszCmdLine,
	int nShowCmd) {

	//初期化パート
	//必要なインスタンスを作成、初期化

	InputManager inputManager;
	
	Game game = Game(inputManager, hInstance);
	Window window(hInstance, nShowCmd, &inputManager, game);
	//
	game.registerWindow(&window);
	game.changeState(new TitleScreenState(game));
	//初期画面レンダリング
	window.render(game.getCurrentState()->getGameObjectManager());
	//初期画面表示
	window.show();
	mainLoop(&game, &window);

	//終了処理
	//WM_QUITメッセージがもう出されているので、はやく終わる。
	window.termination();

	return 0;
}

void mainLoop(Game* game,Window* window) {
	while (window->update(game)) {// WM_QUITメッセージが受信されたらループを終了
	}
	//WM_QUITを受け取るとループを抜ける
}