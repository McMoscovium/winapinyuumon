#pragma once

#include "GameObject.h"

#include "BatBoundingBox.h"
#include <memory>

#include <Windows.h>

class Vector2D;
class InputManager;
class Ball;
class PlayingState;

class Batter:
	public GameObject
{
public:
	Batter(LPCTSTR path, std::wstring objectName, SIZE frameSize, PlayingState& context);
	//�X�C���O���̃q�b�e�B���O����
	bool isHit(Ball);
	//inputManager�̏��ɏ]���ăo�b�^�[�̈ʒu�X�V
	void updateBatterPos(const InputManager& inputManager);
	void updateSwingAnimation(const InputManager& inputManager);
	void updateBatBoundingBox(int currentBatterFrame);
	//animateBatter()�Ɏg���ϐ�
	bool releasedLeftButtonUntilSwingEnded = false;
	//�o�b�^�[�̈ړ��X�s�[�h
	int moveSpeed = 4;
	//�o�b�^�[���ړ��\�Ȕ͈�
	const RECT batterBox;
	//
	POINT nextBatterPos(POINT position, Vector2D movement);
	
	
	
	//�q�b�e�B���O�J�[�\���̈ʒu
	POINT cursorPos()const;
	//�o�b�e�B���O�J�[�\����X���W
	LONG cursorX();
	//�o�b�e�B���O�J�[�\����Y���W
	LONG cursorY();
private:
	PlayingState& context;
};