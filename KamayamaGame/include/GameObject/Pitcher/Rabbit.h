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
			35, 34,
			IDB_BITMAP43,
			hInstance,
			SIZE{ 168,266 }
		)
	{
		pitchTypes.push_back(new AccelBall(3.0f));
	}
	void decideNextPitch()override {
		//球種決定
		currentPitchNumber = 0;
		//球速
		setPitchingSpeed(pitchTypes.at(currentPitchNumber)->decideVelocity(*this));
		//コース
		std::random_device rd;
		std::mt19937 gen(rd()); // メルセンヌ・ツイスタ乱数生成器
		std::uniform_real_distribution<float> dis2(-10.0f, 5.0f);
		setPitchingCourse(dis2(gen));
		//上下方向の初速
		setHVelocity(pitchTypes[currentPitchNumber]->decideHVelocity());
	}
};