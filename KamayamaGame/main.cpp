#include<Windows.h>

#include"Game.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInst,
	LPSTR lpszCmdLine,
	int nCmdShow) {

	Game game;
	game.initializeWindow("釜山ゲーム", "アイコン.ico", "システムアイコン.ico", Game::SEQ_TITLE);

	while(!(game.terminateFlag())) {
		game.mainloop();
	}

	game.terminate();
}