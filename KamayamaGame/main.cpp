#include <Windows.h>
#include "Window.h"
#include "Game.h"
#include "InputManager.h"
#include <memory>
#include "TitleScreenState.h"

using namespace std;

//�J���p
#include <iostream>

const LPCWSTR gameName = L"�N�}�̊��R�̃z�[�������_�[�r�[�I";


void mainLoop(Window& window);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInst,
	LPSTR lpszCmdLine,
	int nShowCmd) {


	//�������p�[�g
	//�K�v�ȃC���X�^���X���쐬�A������
	Game game = Game();
	Window window(hInstance, nShowCmd, &game);

	unique_ptr<TitleScreenState> newState = make_unique<TitleScreenState>(game);
	

	//������ʃ����_�����O
	window.render(game.getCurrentState());
	//������ʕ\��
	window.show();
	mainLoop(window);

	//�I������
	//WM_QUIT���b�Z�[�W�������o����Ă���̂ŁA�͂₭�I���B
	window.termination();
	game.termination();

	return 0;
}

void mainLoop(Window& window) {
	while (window.update()) {// WM_QUIT���b�Z�[�W����M���ꂽ�烋�[�v���I��
	}
	//WM_QUIT���󂯎��ƃ��[�v�𔲂���
}