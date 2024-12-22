#include "PitchType/ChangeUp.h"

#include "GameObject/Ball.h"

#include <random>

void ChangeUp::update(Ball& ball, int frame) {
	//なにもしない
	return;
}

float ChangeUp::decideAngle()
{
	std::random_device rd;
	std::mt19937 gen(rd()); // メルセンヌ・ツイスタ乱数生成器
	std::uniform_real_distribution<float> dis(-7.0f, 7.0f);

	return dis(gen);
}

int ChangeUp::decideVelocity(Pitcher& pitcher)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis2(int(pitcher.getArmStrength() * 0.5f), pitcher.getArmStrength());//一様確率分布
	return dis2(gen);
}
