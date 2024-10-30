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

	//�J���p�R���\�[��
	// �R���\�[���E�B���h�E���쐬
	AllocConsole();

	// �W���o�͂��R���\�[���Ƀ��_�C���N�g
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);  // stdout���R���\�[���Ƀ��_�C���N�g
	//�ȏ�J���p


	//�������p�[�g
	//�K�v�ȃC���X�^���X���쐬�A������
	Game game;
	Window window(hInstance, nShowCmd);
	InputManager inputManager;

	//������ʃ����_�����O
	window.render(&game);
	//������ʕ\��
	window.show();

	//���C�����[�v
	mainLoop(&game, &window, &inputManager);

	//�J���p
	std::cout << "���C�����[�v�I��" << std::endl;

	//�I������
	//WM_QUIT���b�Z�[�W�������o����Ă���̂ŁA�͂₭�I���B
	termination();

	// �R���\�[���������ŕ��Ȃ��悤�ɂ���
	std::cout << "Press Enter to exit...";
	std::cin.get();

	// �R���\�[�������
	FreeConsole();

	return 0;
}

void mainLoop(Game* game,Window* window, InputManager* inputManager) {
	while (window->defaultUpdate()) {// WM_QUIT���b�Z�[�W����M���ꂽ�烋�[�v���I��
		//���b�Z�[�W����
		inputManager->update();
		//�Q�[���̏�Ԃ��X�V
		game->update(inputManager);
		//�Q�[����ʂ̃����_�����O
		window->render(game);
		//�X�V������ʂ�\��
		window->show();
	}
}

void termination() {

}