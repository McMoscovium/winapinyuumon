#include "PitchType/Straight.h"

#include "GameObject/Ball.h"

#include <random>

void Straight::update(Ball& ball, int frame)
{
	//�X�g���[�g�Ȃ̂ŉ������Ȃ�
}

float Straight::decideAngle()
{
	std::random_device rd;
	std::mt19937 gen(rd()); // �����Z���k�E�c�C�X�^����������
	std::uniform_real_distribution<float> dis(-7.0f, 7.0f);

	return dis(gen);
}
