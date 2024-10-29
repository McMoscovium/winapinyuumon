#pragma once

/*
PC�����ł̃Q�[���̐i�s���Ǘ�����N���X�B
���z��ʂւ̕`����s���B
*/


class GameState;
class VirtualWindow;
class Window;

class Game
{
private:
	GameState* currentState;
	VirtualWindow* virtualWindow;

	void drawWindow();//���z��ʂɃQ�[����ʂ�`�悷��
	
public:
	Game();
	Game(Window* window);//�E�B���h�E���肫�̃R���X�g���N�^�B���z�E�B���h�E�̐ݒ���s���B
	~Game();

	void update();//�Q�[����Ԃ��Ƃɐݒ肳�ꂽ�X�V�������s��
	void changeState(GameState* newState);//��Ԃ�ύX����
	void setBackBuffer(Window* window);//virtualWindow�̏����ݒ�
};