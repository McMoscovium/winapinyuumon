#include "Tintin.h"
#include <random>

void Tintin::decideNextPitch()
{
	//����͍��̓X�g���[�g�Œ�

	//����
	std::random_device rd;
	std::mt19937 gen(rd()); // �����Z���k�E�c�C�X�^����������
	std::uniform_int_distribution<> dis1(getArmStrength() - 10, getArmStrength());//��l�m�����z
	setPitchingSpeed(dis1(gen));

	//�R�[�X
	std::uniform_int_distribution<> dis2(-100, 100);
	setPitchingCourse(dis2(gen));
}
