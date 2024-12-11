#pragma once

#include "util/Vector2D.h"
#include <Windows.h>
#include "GameObject/Pitcher/Pitcher.h"


class Window;

class Ball
{
private:
	//
	int radius = 20;
	//ゲーム上の位置（ホームベースが原点）
	POINT position;
	//平面上の向き（センターが０、レフトポールが+45、ライトポールが-45）
	float angle = 0;
	//平面上の早さ
	int velocity = 0;
	//高さ方向の速度
	float hVelocity = 0;
	//高さ
	float height = 70.0f;
	//
	float gravity=0.5f;
	//球種に合わせてvelocityを計算
	void updateByPitchType(Pitcher* pitcher);
	//リリースされてからのフレーム数
	int framesSinceReleased = 0;

public:
	Ball();
	
	float getAngle()const;
	int getVelocity()const;
	float getHVelocity()const;
	float getHeight()const;
	POINT getPosition()const;
	LONG getX()const;
	LONG getY()const;
	int getRadius()const;
	float getGravity()const;

	void setAngle(const float);
	void setVelocity(const int);
	void sethVelocity(const float);
	void setPosition(POINT pos);
	void setHeight(float h);
	void resetFrame();

	//pitcherの球種に合わせてボールの位置を更新
	POINT updatePitch(Pitcher* pitcher);
};