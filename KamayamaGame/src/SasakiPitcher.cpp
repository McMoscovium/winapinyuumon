#include "SasakiPitcher.h"

#include <random>

void SasakiPitcher::decideNextPitch()
{
	//球種は今はストレート固定

	//球速
	std::random_device rd;
	std::mt19937 gen(rd()); // メルセンヌ・ツイスタ乱数生成器
	std::uniform_int_distribution<> dis1((int)(getArmStrength() * 0.7), getArmStrength());//一様確率分布
	setPitchingSpeed(dis1(gen));

	//コース
	std::uniform_real_distribution<float> dis2(-10.0f, 5.0f);
	setPitchingCourse(dis2(gen));
}

bool SasakiPitcher::nextFrame()
{
	if (frameNumber == length - 1) {
		frameNumber = 0;
		return true;
	}
	
	if (isOddFrame) {
		frameNumber++;
		isOddFrame = false;
		return true;
	}
	else {
		isOddFrame = true;
		return true;
	}
}
