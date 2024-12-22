#pragma once

#include "Pitcher.h"

#include "PitchType/OwlBall.h"

#include "resource.h"
#include <random>

class OwlPitcher : public Pitcher
{
private:
public:
	OwlPitcher(HINSTANCE hInstance) :
		Pitcher(
			L"Owl",
			27,
			27,
			IDB_BITMAP38,
			hInstance,
			SIZE{ 200,266 }
		) {
		pitchTypes.push_back(new OwlBall());
	}
	void decideNextPitch()override {
		//�����I��
		currentPitchNumber = 0;
		//����
		std::random_device rd;
		std::mt19937 gen(rd()); // �����Z���k�E�c�C�X�^����������
		std::uniform_int_distribution<> dis1((int)(getArmStrength() * 0.7), getArmStrength());//��l�m�����z
		setPitchingSpeed(dis1(gen));

		//�R�[�X
		float angle = pitchTypes.at(currentPitchNumber)->decideAngle();
		setPitchingCourse(angle);
	}
};