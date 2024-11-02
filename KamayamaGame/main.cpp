#include <Windows.h>
#include "Window.h"
#include "Game.h"
#include "InputManager.h"

//�J���p
#include <iostream>

const LPCWSTR gameName = L"�N�}�̊��R�̃z�[�������_�[�r�[�I";


void mainLoop(Game* game,Window* window,InputManager* inputManager);
void termination();

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInst,
	LPSTR lpszCmdLine,
	int nShowCmd) {


	//�������p�[�g
	//�K�v�ȃC���X�^���X���쐬�A������
	Game game;
	InputManager inputManager;
	Window window(hInstance, nShowCmd, &game, &inputManager);
	

	//������ʃ����_�����O
	window.render(game.getCurrentState());
	//������ʕ\��
	window.show();
	mainLoop(&game, &window, &inputManager);

	//�I������
	//WM_QUIT���b�Z�[�W�������o����Ă���̂ŁA�͂₭�I���B
	termination();

	return 0;
}

void mainLoop(Game* game,Window* window, InputManager* inputManager) {
	while (window->update(game)) {// WM_QUIT���b�Z�[�W����M���ꂽ�烋�[�v���I��
	}
	//WM_QUIT���󂯎��ƃ��[�v�𔲂���
}

void termination() {//���������������
	
}