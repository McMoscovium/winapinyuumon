#pragma once
#include<Windows.h>

class IGameState;
class Game;
class GameObject;
class InputManager;
class GameObjectManager;

struct UserData {
public:
	Game* game;
	UserData(Game* game) :game(game) {}
};


class Window
{
public:
	const int width = 1152;
	const int height = 720;


	//�R���X�g���N�^�B�E�B���h�E�N���X�̓o�^�A�E�B���h�E�̍쐬�܂ōs���B
	Window(HINSTANCE hInstance, int nCmdShow, InputManager* inputManager, Game& game);
	~Window();

	//
	RECT getClientRect();


	//���݂̃E�B���h�E��\��
	void show() const;

	//Game�N���X�̏��ɏ]���E�B���h�E��`�悵�Ȃ����B
	void render(const GameObjectManager& gameObjectManager)const;

	//�E�B���h�E�n���h�����擾
	HWND getHandle()const { return hwnd; }

	//�f�o�C�X�R���e�L�X�g���擾
	HDC getDC()const;

	UINT getFps()const;

	bool update(Game* game);//�����b�Z�[�W���[�v�ōs�������iWM_DESTROY���̏����j

	//�E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK WindowProc(HWND, UINT uMsg, WPARAM wParam, LPARAM lParam);

	//�I������
	void termination();
	//������̍��W��(0,0)�ƂȂ�
	RECT getClientRect()const;

	//
	bool isInClientRect(POINT point)const {
		RECT rect = getClientRect();
		if (point.x <= rect.right &&
			point.x >= rect.left &&
			point.y <= rect.bottom &&
			point.y >= rect.top
			) {
			return true;
		}
		else {
			return false;
		}
	}

protected:
	
	
private:
	HINSTANCE hInstance;
	HWND hwnd;
	const wchar_t* className = L"SampleWindowClass";
	MSG msg;
	UINT fps = 30;
	UserData* userData = nullptr;

	//�E�B���h�E�N���X�̓o�^
	void registerClass();
	//�E�B���h�E�쐬�B����A�p�����[�^�ނ̕ύX���\�Ȏ����ɕς���B
	void create(Game& game);
	//�E�B���h�E�v���V�[�W���ɓn���C���X�^���X��o�^
	void registerUserData(Game* game);
	//�N���C�A���g�̈�̎l�p�`�̐��@�i�s�N�Z���j���擾
	

	bool getClientRect(RECT* rect)const;
	
};