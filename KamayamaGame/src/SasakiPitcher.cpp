#include "SasakiPitcher.h"

#include <random>

void SasakiPitcher::decideNextPitch()
{
	//����͍��̓X�g���[�g�Œ�

	//����
	std::random_device rd;
	std::mt19937 gen(rd()); // �����Z���k�E�c�C�X�^����������
	std::uniform_int_distribution<> dis1((int)(getArmStrength() * 0.7), getArmStrength());//��l�m�����z
	setPitchingSpeed(dis1(gen));

	//�R�[�X
	std::uniform_real_distribution<float> dis2(-10.0f, 5.0f);
	setPitchingCourse(dis2(gen));
}

bool SasakiPitcher::nextFrame()
{
	if (frameNumber == length - 1) {
		frameNumber = 0;
		return true;
	}
	
	if (isOddFrame) {
		frameNumber++;
		isOddFrame = false;
		return true;
	}
	else {
		isOddFrame = true;
		return true;
	}
}
