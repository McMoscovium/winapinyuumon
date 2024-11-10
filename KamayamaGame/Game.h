#pragma once

/*
PC�����ł̃Q�[���̐i�s���Ǘ�����N���X�B
���z��ʂւ̕`����s���B
*/
#include "unordered_map"
#include "IGameState.h"

class Window;
class InputManager;

class Game
{
private:
	IGameState* currentState = nullptr;
	InputManager& inputManager;
	Window* window;

	
public:
	Game(InputManager& inputManager);
	~Game();


	//
	bool registerWindow(Window* window);
	void update();//�Q�[����Ԃ��Ƃɐݒ肳�ꂽ�X�V�������s��
	void changeState(IGameState* newState);//currentState��ύX����
	//
	const IGameState* getCurrentState()const;
	//
	InputManager& getInputManager() {
		return inputManager;
	}
	//
	Window* getWindow() {
		return window;
	}
};