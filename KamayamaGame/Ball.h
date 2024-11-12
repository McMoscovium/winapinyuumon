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
	//
	int gravity=1;

public:
	Ball();
	
	int getAngle()const;
	int getVelocity()const;
	int getHVelocity()const;
	int getHeight()const;
	POINT getPosition()const;
	LONG getX()const;
	LONG getY()const;
	int getRadius()const;
	int getGravity()const;

	void setAngle(const int);
	void setVelocity(const int);
	void sethVelocity(const int);
	void setPosition(POINT pos);
	void setHeight(int h);
};