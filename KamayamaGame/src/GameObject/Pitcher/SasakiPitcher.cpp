#include "GameObject/Pitcher/SasakiPitcher.h"

#include <random>

void SasakiPitcher::decideNextPitch()
{
	//�����I��
	currentPitchNumber = 1;
	//����
	std::random_device rd;
	std::mt19937 gen(rd()); // �����Z���k�E�c�C�X�^����������
	std::uniform_int_distribution<> dis1((int)(getArmStrength() * 0.7), getArmStrength());//��l�m�����z
	setPitchingSpeed(dis1(gen));

	//�R�[�X
	float angle = pitchTypes.at(currentPitchNumber)->decideAngle();
	setPitchingCourse(angle);
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
