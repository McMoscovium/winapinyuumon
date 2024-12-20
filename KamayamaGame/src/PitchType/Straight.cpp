#include "PitchType/Straight.h"

#include "GameObject/Ball.h"

#include <random>

void Straight::update(Ball& ball, int frame)
{
	//ストレートなので何もしない
}

float Straight::decideAngle()
{
	std::random_device rd;
	std::mt19937 gen(rd()); // メルセンヌ・ツイスタ乱数生成器
	std::uniform_real_distribution<float> dis(-7.0f, 7.0f);

	return dis(gen);
}
