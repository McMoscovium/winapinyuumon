#pragma once

#include "Pitcher.h"

#include "PitchType/OwlBall.h"

#include "resource.h"
#include <random>

class OwlPitcher : public Pitcher
{
private:
public:
	OwlPitcher(HINSTANCE hInstance) :
		Pitcher(
			L"Owl",
			27,
			27,
			IDB_BITMAP38,
			hInstance,
			SIZE{ 200,266 }
		) {
		pitchTypes.push_back(new OwlBall());
	}
	void decideNextPitch()override {
		//球種を選ぶ
		currentPitchNumber = 0;
		//球速
		std::random_device rd;
		std::mt19937 gen(rd()); // メルセンヌ・ツイスタ乱数生成器
		std::uniform_int_distribution<> dis1((int)(getArmStrength() * 0.7), getArmStrength());//一様確率分布
		setPitchingSpeed(dis1(gen));

		//コース
		float angle = pitchTypes.at(currentPitchNumber)->decideAngle();
		setPitchingCourse(angle);
	}
};