#include "TintinPitcher.h"
#include <random>

void TintinPitcher::decideNextPitch()
{
	//球種は今はストレート固定

	//球速
	std::random_device rd;
	std::mt19937 gen(rd()); // メルセンヌ・ツイスタ乱数生成器
	std::uniform_int_distribution<> dis1(getArmStrength()*0.7, getArmStrength());//一様確率分布
	setPitchingSpeed(dis1(gen));

	//コース
	std::uniform_real_distribution<float> dis2(-10.0f, 5.0f);
	setPitchingCourse(dis2(gen));
}
