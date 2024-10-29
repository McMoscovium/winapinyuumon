#include <Windows.h>
#include "Window.h"
#include "Game.h"
#include "InputManager.h"

//�J���p
#include <iostream>

const LPCWSTR gameName = L"�N�}�̊��R�̃z�[�������_�[�r�[�I";




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


	//�K�v�ȃC���X�^���X���쐬�A������
	Window window(hInstance, nShowCmd);
	Game game(&window);
	InputManager inputManager;

	//���C�����[�v
	MSG msg = {};
	while (true) {
		//���b�Z�[�W����
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			//�I�����b�Z�[�W�̏ꍇ
			if (msg.message == WM_QUIT) {
				return 0;//�A�v�����I��
			}
		}
		//�I�����b�Z�[�W�łȂ��ꍇ
		//���͂̍X�V
		inputManager.update();
		//�Q�[���̏�Ԃ��X�V
		game.update(&inputManager);
		//�X�V������ʂ�\��
		window.show();
	}


	// �R���\�[���������ŕ��Ȃ��悤�ɂ���
	std::cout << "Press Enter to exit...";
	std::cin.get();

	// �R���\�[�������
	FreeConsole();

	return 0;
}