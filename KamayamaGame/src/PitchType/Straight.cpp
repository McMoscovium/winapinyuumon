#include "PitchType/Straight.h"

#include "GameObject/Ball.h"

#include <random>

void Straight::update(Ball& ball, int frame)
{
	//�኱��������
	int nextVelocity = ((acceleration - 1) * initialVelocity * ball.getY() + initialVelocity * (653 - acceleration * 122)) /
		(653 - 122);
	ball.setVelocity(nextVelocity);
}

float Straight::decideAngle()
{
	std::random_device rd;
	std::mt19937 gen(rd()); // �����Z���k�E�c�C�X�^����������
	std::uniform_real_distribution<float> dis(-7.0f, 7.0f);

	return dis(gen);
}
