#pragma once

#include "Vector2D.h"
#include <Windows.h>


class Window;

class Ball
{
private:
	//���ʏ�̌����i�Z���^�[���O�A���t�g�|�[����+45�A���C�g�|�[����-45�j
	int angle = 0;
	//���ʏ�̑���
	int velocity = 0;
	//���������̑��x
	int hVelocity = 0;
	//����
	int height = 0;
	//�����ɂ���ĕς��A�{�[���̌������̑傫���̔{��
	float sizeRatio = 1;
	//�e��



public:
	Ball();
	
	int getAngle()const;
	int getVelocity()const;
	void setAngle(const int);
	void setVelocity(const int);
	void sethVelocity(const int);
};