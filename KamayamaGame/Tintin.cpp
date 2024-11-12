#include "Tintin.h"
#include <random>

void Tintin::decideNextPitch()
{
	//球種は今はストレート固定

	//球速
	std::random_device rd;
	std::mt19937 gen(rd()); // メルセンヌ・ツイスタ乱数生成器
	std::uniform_int_distribution<> dis1(getArmStrength() - 10, getArmStrength());//一様確率分布
	setPitchingSpeed(dis1(gen));

	//コース
	std::uniform_int_distribution<> dis2(-100, 100);
	setPitchingCourse(dis2(gen));
}
