#pragma once

#include "GameObject/Pitcher/Pitcher.h"

#include "PitchType/ChangeUp.h"
#include "PitchType/Straight.h"
#include "PitchType/WhiteBall.h"
#include "PitchType/AccelBall.h"
#include "PitchType/OwlBall.h"
#include "PitchType/VanishBall.h"

#include <random>

#include "resource.h"

class Robin :
	public Pitcher
{
private:
public:
	Robin(HINSTANCE hInstance) :
		Pitcher(
			L"Robin",
			30, 34,
			IDB_BITMAP43,
			hInstance,
			SIZE{ 168,266 }
		)
	{
		pitchTypes.push_back(new ChangeUp());
		pitchTypes.push_back(new Straight(1.3f));
		pitchTypes.push_back(new Straight());
		pitchTypes.push_back(new WhiteBall());
		pitchTypes.push_back(new AccelBall());
		pitchTypes.push_back(new OwlBall());
		pitchTypes.push_back(new VanishBall());
	}

	void decideNextPitch()override {
		std::random_device rd;
		std::mt19937 gen(rd()); // メルセンヌ・ツイスタ乱数生成器

		//球種決定
		std::uniform_int_distribution<> dis1(0, (int)pitchTypes.size()-1);
		currentPitchNumber = dis1(gen);

		//球速
		std::uniform_int_distribution<> dis2(int(getArmStrength() * 0.5f), getArmStrength());//一様確率分布
		setPitchingSpeed(dis2(gen));
		//コース
		std::uniform_real_distribution<float> dis3(-10.0f, 5.0f);
		setPitchingCourse(dis3(gen));
		//上下方向の初速
		setHVelocity(pitchTypes[currentPitchNumber]->decideHVelocity());
	}
};