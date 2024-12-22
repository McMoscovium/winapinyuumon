#include "PitchType/AccelBall.h"

#include "GameObject/Ball.h"
#include <random>

AccelBall::AccelBall():
	PitchType(L"ACCELBALL"),
	accelRate(3.0f),
	beginAccelY(309),
	acceleration(2.0f)
{
}

void AccelBall::update(Ball& ball, int frame)
{
	int Y = ball.getY();
	//Y>beginAccelY����}���ɉ���
	if (Y < beginAccelY)return;

	int nextVelocity = accelRate * initialVelocity * ((acceleration - 1) * Y + 653 - acceleration * beginAccelY) / (653 - beginAccelY);
	ball.setVelocity(nextVelocity);
	return;
}

float AccelBall::decideAngle()
{
	std::random_device rd;
	std::mt19937 gen(rd()); // �����Z���k�E�c�C�X�^����������
	std::uniform_real_distribution<float> dis(-7.0f, 7.0f);

	return dis(gen);
}

int AccelBall::decideVelocity(Pitcher& pitcher)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis2((int)(pitcher.getArmStrength()*0.2f), (int)(pitcher.getArmStrength()*0.3f));//��l�m�����z
	return dis2(gen);
}
