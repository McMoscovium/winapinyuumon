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