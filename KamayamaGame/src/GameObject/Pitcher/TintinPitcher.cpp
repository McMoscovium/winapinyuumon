#include "GameObject/Pitcher/TintinPitcher.h"
#include <random>

void TintinPitcher::decideNextPitch()
{
	//���팈��
	currentPitchNumber = 2;

	//����
	std::random_device rd;
	std::mt19937 gen(rd()); // �����Z���k�E�c�C�X�^����������
	std::uniform_int_distribution<> dis1(int(getArmStrength()*0.7f), getArmStrength());//��l�m�����z
	setPitchingSpeed(dis1(gen));

	//�R�[�X
	std::uniform_real_distribution<float> dis2(-10.0f, 5.0f);
	setPitchingCourse(dis2(gen));

	//�㉺�����̏���
	setHVelocity(pitchTypes[currentPitchNumber]->decideHVelocity());
}
