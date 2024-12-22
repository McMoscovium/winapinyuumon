#include "PitchType/Slider.h"

#include "GameObject/Ball.h"
#include <random>

void Slider::update(Ball& ball, int frame)
{
	OutputDebugString(L"変化中\n");
	LONG Y = ball.getY();
	if (Y < startCurvingY) return;
	//Y >= startCurvingYでカーブ開始

	float currentAngle = ball.getAngle();
	float nextAngle = currentAngle + diff;
	ball.setAngle(nextAngle);
	
	return;
}

float Slider::decideAngle()
{
	std::random_device rd;
	std::mt19937 gen(rd()); // メルセンヌ・ツイスタ乱数生成器
	std::uniform_real_distribution<float> dis(-2.0f, 12.0f);

	return dis(gen);
}

int Slider::decideVelocity(Pitcher& pitcher) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis2(int(pitcher.getArmStrength() * 0.5f), pitcher.getArmStrength());//一様確率分布
	return dis2(gen);
}