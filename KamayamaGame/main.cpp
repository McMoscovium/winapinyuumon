#include<Windows.h>

#include"Game.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInst,
	LPSTR lpszCmdLine,
	int nCmdShow) {

	Game game;
	game.initializeWindow("���R�Q�[��", "�A�C�R��.ico", "�V�X�e���A�C�R��.ico", Game::SEQ_TITLE);

	while(!(game.terminateFlag())) {
		game.mainloop();
	}

	game.terminate();
}