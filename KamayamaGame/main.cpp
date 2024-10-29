#include<Windows.h>
#include"Window.h"
#include"Game.h"
#include "InputManager.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInst,
	LPSTR lpszCmdLine,
	int nShowCmd) {

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
		game.update();
		//�X�V������ʂ�\��
		window.show();
	}
	return 0;
}