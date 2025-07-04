#include "PitchType/OwlBall.h"

#include "GameObject/Ball.h"
#include <random>

void OwlBall::update(Ball& ball, int frame)
{
	//ボールの変分をy座標によって変える
	int currentVelocity = ball.getVelocity();
	int nextVelocity = currentVelocity + 1;
	ball.setVelocity(nextVelocity);



	bool isChangeFrame = frame % frequency == 0;//フレーム数が5の倍数のとき曲がる
	if (!isChangeFrame) return;

	float currentAngle = ball.getAngle();
	float nextAngle = 0;
	bool arity = frame % (frequency * 2) == 0;
	if (arity) {
		nextAngle = currentAngle + sharpness * 2;
	}
	else {
		nextAngle = currentAngle - sharpness * 2;
	}
	ball.setAngle(nextAngle);
	return;
}

float OwlBall::decideAngle()
{
	std::random_device rd;
	std::mt19937 gen(rd()); // メルセンヌ・ツイスタ乱数生成器
	float low = sharpness - 12, high = sharpness - 4;
	std::uniform_real_distribution<float> dis(low, high);

	return dis(gen);
}

int OwlBall::decideVelocity(Pitcher& pitcher) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis2(int(pitcher.getArmStrength() * 0.5f), pitcher.getArmStrength());//一様確率分布
	return dis2(gen);
}
