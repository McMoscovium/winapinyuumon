#pragma once
#include<Windows.h>
#include <memory>

#include "IGameState.h"

class Game;
class GameObject;
class Window;
class InputManager;

struct UserData {
public:
	Game* game;
	Window* window;
	UserData(Game* game,Window* window) :
		game(game),
		window(window)
	{}
};


class Window
{
public:
	const int width = 1152;
	const int height = 720;


	//�R���X�g���N�^�B�E�B���h�E�N���X�̓o�^�A�E�B���h�E�̍쐬�܂ōs���B
	Window(HINSTANCE hInstance, int nCmdShow, Game* game);
	~Window();

	//���݂̃E�B���h�E��\��
	void show() const;

	//Game�N���X�̏��ɏ]���E�B���h�E��`�悵�Ȃ����B
	void render(const std::unique_ptr<IGameState>& currentState);

	//�E�B���h�E�n���h�����擾
	HWND getHandle()const { return hwnd; }

	//�f�o�C�X�R���e�L�X�g���擾
	HDC getDC()const;

	UINT getFps()const;

	bool update();//�����b�Z�[�W���[�v�ōs�������iWM_DESTROY���̏����j

	//�E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK WindowProc(HWND, UINT uMsg, WPARAM wParam, LPARAM lParam);

	//�I������
	void termination();

private:
	HINSTANCE hInstance;
	HWND hwnd;
	const wchar_t* className = L"SampleWindowClass";
	MSG msg;
	UINT fps = 30;
	std::unique_ptr<UserData> userData = nullptr;

	//�E�B���h�E�N���X�̓o�^
	void registerClass();
	//�E�B���h�E�쐬�B����A�p�����[�^�ނ̕ύX���\�Ȏ����ɕς���B
	void create(Game* game);
	//�E�B���h�E�v���V�[�W���ɓn���C���X�^���X��o�^
	void registerUserData(Game* game);
	//�N���C�A���g�̈�̎l�p�`�̐��@�i�s�N�Z���j���擾
	//������̍��W��(0,0)�ƂȂ�
	void getClientRect(RECT* rect)const;
	//�n���ꂽ�Q�[���I�u�W�F�N�g��HDC�̑I������f�o�C�X�ɕ`��i���ߐF���l���j
	void renderGameObject(const GameObject& gameObject, HDC hdc)const;
};