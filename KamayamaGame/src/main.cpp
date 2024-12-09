#include <Windows.h>
#include "Window.h"
#include "Game.h"
#include "InputManager.h"
#include "TitleScreenState.h"


//�J���p
#include <iostream>

const LPCWSTR gameName = L"�N�}�̊��R�̃z�[�������_�[�r�[�I";


void mainLoop(Game* game,Window* window);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInst,
	LPSTR lpszCmdLine,
	int nShowCmd) {

	//�������p�[�g
	//�K�v�ȃC���X�^���X���쐬�A������

	InputManager inputManager;
	
	Game game = Game(inputManager, hInstance);
	Window window(hInstance, nShowCmd, &inputManager, game);
	//
	game.registerWindow(&window);
	game.changeState(new TitleScreenState(game));
	//������ʃ����_�����O
	window.render(game.getCurrentState()->getGameObjectManager());
	//������ʕ\��
	window.show();
	mainLoop(&game, &window);

	//�I������
	//WM_QUIT���b�Z�[�W�������o����Ă���̂ŁA�͂₭�I���B
	window.termination();

	return 0;
}

void mainLoop(Game* game,Window* window) {
	while (window->update(game)) {// WM_QUIT���b�Z�[�W����M���ꂽ�烋�[�v���I��
	}
	//WM_QUIT���󂯎��ƃ��[�v�𔲂���
}