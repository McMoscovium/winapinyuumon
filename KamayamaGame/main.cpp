#include<Windows.h>

#include"Game.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInst,
	LPSTR lpszCmdLine,
	int nCmdShow) {

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