#include "GameObject/Pitcher/TintinPitcher.h"
#include <random>

void TintinPitcher::decideNextPitch()
{
	//球種決定
	currentPitchNumber = 2;

	//球速
	std::random_device rd;
	std::mt19937 gen(rd()); // メルセンヌ・ツイスタ乱数生成器
	std::uniform_int_distribution<> dis1(int(getArmStrength()*0.7f), getArmStrength());//一様確率分布
	setPitchingSpeed(dis1(gen));

	//コース
	std::uniform_real_distribution<float> dis2(-10.0f, 5.0f);
	setPitchingCourse(dis2(gen));

	//上下方向の初速
	setHVelocity(pitchTypes[currentPitchNumber]->decideHVelocity());
}
