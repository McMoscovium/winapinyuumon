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
	float hVelocity = 0;
	//����
	float height = 70.0f;
	//
	float gravity=0.5f;

public:
	Ball();
	
	int getAngle()const;
	int getVelocity()const;
	float getHVelocity()const;
	float getHeight()const;
	POINT getPosition()const;
	LONG getX()const;
	LONG getY()const;
	int getRadius()const;
	float getGravity()const;

	void setAngle(const int);
	void setVelocity(const int);
	void sethVelocity(const float);
	void setPosition(POINT pos);
	void setHeight(float h);
};