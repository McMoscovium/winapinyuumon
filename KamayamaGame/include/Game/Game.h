#pragma once

/*
PC�����ł̃Q�[���̐i�s���Ǘ�����N���X�B
���z��ʂւ̕`����s���B
*/
#include <unordered_map>
#include "GameState/IGameState.h"
#include "Camera.h"
#include "Version.h"

class Window;
class InputManager;

class Game
{
private:
	Version version = Version(0, 0, 1);
	IGameState* currentState = nullptr;
	InputManager& inputManager;
	Window* window;
	Camera camera;
	int money = 0;
	const HINSTANCE& hInstance;//�A�v���P�[�V�����̃C���X�^���X�̓��h���B���\�[�X���g���̂ɂ���B

	
public:
	Game(InputManager& inputManager, const HINSTANCE& hInstance);
	~Game();


	//
	bool registerWindow(Window* window);
	void update();//�Q�[����Ԃ��Ƃɐݒ肳�ꂽ�X�V�������s��
	void changeState(IGameState* newState);//currentState��ύX����
	//
	IGameState* getCurrentState()const;
	//
	InputManager& getInputManager() {
		return inputManager;
	}
	//
	Window* getWindow() {
		return window;
	}
	const HINSTANCE& getHInstance();
	const Version& getCurrentVersion()const { return version; }
};