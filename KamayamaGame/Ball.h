#pragma once

#include "Vector2D.h"
#include <Windows.h>


class Window;

class Ball
{
private:
	//
	int radius = 20;
	//ゲーム上の位置（ホームベースが原点）
	POINT position;
	//平面上の向き（センターが０、レフトポールが+45、ライトポールが-45）
	int angle = 0;
	//平面上の早さ
	int velocity = 0;
	//高さ方向の速度
	float hVelocity = 0;
	//高さ
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