#pragma once

/*
PC�����ł̃Q�[���̐i�s���Ǘ�����N���X�B
���z��ʂւ̕`����s���B
*/
#include "unordered_map"

class GameState;
class VirtualWindow;
class Window;
class InputManager;
class ObjectName;

class Game
{
private:
	GameState* currentState;

	void drawWindow();//���z��ʂɃQ�[����ʂ�`�悷��

	
public:
	Game();
	~Game();

	void update(InputManager* inputManager);//�Q�[����Ԃ��Ƃɐݒ肳�ꂽ�X�V�������s��
	void changeState(GameState* newState);//currentState��ύX����
	void setBackBuffer(Window* window);//virtualWindow�̏����ݒ�
	const GameState* getCurrentState()const;
	//�I������
	void termination();
};