#pragma once
#include<Windows.h>

class Game;

class Window
{
public:
	const int width = 800;
	const int height = 600;


	//�R���X�g���N�^�B�E�B���h�E�N���X�̓o�^�A�E�B���h�E�̍쐬�A�E�B���h�E�̕\���܂ōs���B
	Window(HINSTANCE hInstance, int nCmdShow);
	~Window();

	void show();

	//�E�B���h�E�n���h�����擾
	HWND getHandle()const { return hwnd; }

	//�f�o�C�X�R���e�L�X�g���擾
	HDC getDC()const;

protected:
	//�E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK WindowProc(HWND, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
private:
	HINSTANCE hInstance;
	HWND hwnd;
	const wchar_t* className = L"SampleWindowClass";
	

	//�E�B���h�E�N���X�̓o�^
	void registerClass();
	//�E�B���h�E�쐬�B����A�p�����[�^�ނ̕ύX���\�Ȏ����ɕς���
	void create();
	
};

