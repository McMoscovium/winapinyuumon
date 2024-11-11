#pragma once

#include "Vector2D.h"
#include <Windows.h>


class Window;

class Ball
{
private:
	//平面上の向き（センターが０、レフトポールが+45、ライトポールが-45）
	int angle = 0;
	//平面上の早さ
	int velocity = 0;
	//高さ方向の速度
	int hVelocity = 0;
	//高さ
	int height = 0;
	//高さによって変わる、ボールの見かけの大きさの倍率
	float sizeRatio = 1;
	//親玉



public:
	Ball();
	
	int getAngle()const;
	int getVelocity()const;
	void setAngle(const int);
	void setVelocity(const int);
	void sethVelocity(const int);
};