#pragma once

/*
PC�����ł̃Q�[���̐i�s���Ǘ�����N���X�B
���z��ʂւ̕`����s���B
*/


#include <memory>
#include "AudioManager.h"
#include "InputManager.h"
#include "IGameState.h"

class Window;


class Game
{
private:
	std::unique_ptr<IGameState> currentState = nullptr;
	InputManager inputManager;
	AudioManager audioManager;

public:
	Game();
	~Game();

	//currentState��ύX����
	void changeState(std::unique_ptr<IGameState> newState) {
		currentState = std::move(newState);
	}

	//�I������
	void termination();

	//const�ł̃Q�b�^�[
	const InputManager& getConstInputManager()const;
	//mutable�ł̃Q�b�^�\
	InputManager& getInputManager();
	//
	const std::unique_ptr<IGameState>& getCurrentState()const;
};