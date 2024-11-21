#include "TintinPitcher.h"
#include <random>

void TintinPitcher::decideNextPitch()
{
	//����͍��̓X�g���[�g�Œ�

	//����
	std::random_device rd;
	std::mt19937 gen(rd()); // �����Z���k�E�c�C�X�^����������
	std::uniform_int_distribution<> dis1(getArmStrength()*0.7, getArmStrength());//��l�m�����z
	setPitchingSpeed(dis1(gen));

	//�R�[�X
	std::uniform_real_distribution<float> dis2(-10.0f, 5.0f);
	setPitchingCourse(dis2(gen));
}
