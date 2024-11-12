#pragma once

#include "Vector2D.h"
#include <Windows.h>


class Window;

class Ball
{
private:
	//
	int radius = 20;
	//�Q�[����̈ʒu�i�z�[���x�[�X�����_�j
	POINT position;
	//���ʏ�̌����i�Z���^�[���O�A���t�g�|�[����+45�A���C�g�|�[����-45�j
	int angle = 0;
	//���ʏ�̑���
	int velocity = 0;
	//���������̑��x
	int hVelocity = 0;
	//����
	int height = 70;
	//�J�����ƃ{�[���̋����ɂ���ĕς��A�{�[���̌������̑傫���̔{��
	float sizeRatio = 1;

public:
	Ball();
	
	int getAngle()const;
	int getVelocity()const;
	int getHeight()const;
	POINT getPosition()const;
	LONG getX()const;
	LONG getY()const;
	int getRadius()const;

	void setAngle(const int);
	void setVelocity(const int);
	void sethVelocity(const int);
	void setPosition(POINT pos);
};