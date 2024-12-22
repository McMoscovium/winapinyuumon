#include "PitchType/OwlBall.h"

#include "GameObject/Ball.h"
#include <random>

void OwlBall::update(Ball& ball, int frame)
{
	//�{�[���̕ϕ���y���W�ɂ���ĕς���
	int currentVelocity = ball.getVelocity();
	int nextVelocity = currentVelocity + 1;
	ball.setVelocity(nextVelocity);



	bool isChangeFrame = frame % frequency == 0;//�t���[������5�̔{���̂Ƃ��Ȃ���
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
	std::mt19937 gen(rd()); // �����Z���k�E�c�C�X�^����������
	float low = sharpness - 12, high = sharpness - 4;
	std::uniform_real_distribution<float> dis(low, high);

	return dis(gen);
}

int OwlBall::decideVelocity(Pitcher& pitcher) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis2(int(pitcher.getArmStrength() * 0.5f), pitcher.getArmStrength());//��l�m�����z
	return dis2(gen);
}
