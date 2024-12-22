#pragma once

#include "GameObject/Pitcher/Pitcher.h"

#include "PitchType/AccelBall.h"
#include <random>

#include "resource.h"

class Rabbit :
	public Pitcher
{
private:
public:
	Rabbit(HINSTANCE hInstance) :
		Pitcher(
			L"rabbit",
			13, 34,
			IDB_BITMAP43,
			hInstance,
			SIZE{ 168,266 }
		)
	{
		pitchTypes.push_back(new AccelBall());
	}
	void decideNextPitch()override {
		//球種決定
		currentPitchNumber = 0;
		//球速
		std::random_device rd;
		std::mt19937 gen(rd()); // メルセンヌ・ツイスタ乱数生成器
		std::uniform_int_distribution<> dis1(int(getArmStrength() * 0.7f), getArmStrength());//一様確率分布
		setPitchingSpeed(dis1(gen));
		//コース
		std::uniform_real_distribution<float> dis2(-10.0f, 5.0f);
		setPitchingCourse(dis2(gen));
		//上下方向の初速
		setHVelocity(pitchTypes[currentPitchNumber]->decideHVelocity());
	}
};