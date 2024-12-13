#include <Windows.h>
#include "Game/Window.h"
#include "Game/Game.h"
#include "Game/InputManager.h"
#include "GameState/TitleScreenState/TitleScreenState.h"


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

	//�E�B���h�E�֌W
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
	LARGE_INTEGER frequency, start, end;//�^�C�}�[�֌W
	double elapsed;
	QueryPerformanceFrequency(&frequency);//���g��
	QueryPerformanceCounter(&start);//�J�n���J�E���g

	while (window->update(game)) {// WM_QUIT���b�Z�[�W����M���ꂽ�烋�[�v���I��
		//�E�B���h�E�v���V�[�W���I�����J�E���g
		QueryPerformanceCounter(&end);
		//�o�ߎ���
		elapsed = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
		//1�t���[�����̎��Ԃ����܂ő҂�
		if (elapsed > 1.0 / window->getFps()) {
			//1�t���[���̎��Ԃ��o��
			//60�b��1��Ăяo��
			//�Q�[�����W�b�N���A�b�v�f�[�g
			game->getInputManager().update();
			game->update();
			//�ĕ`��v��
			InvalidateRect(window->getHandle(), NULL, FALSE);
			QueryPerformanceCounter(&start); // ���̃t���[���̊���Ԃ�ݒ�
		}
	}
	//WM_QUIT���󂯎��ƃ��[�v�𔲂���
}