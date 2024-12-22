#pragma once

#include "GameObject/Pitcher/Pitcher.h"

#include "PitchType/AccelBall.h"
#include <random>

#include "resource.h"

class Rabbit :
	public Pitcher
{
private:
public:
	Rabbit(HINSTANCE hInstance) :
		Pitcher(
			L"rabbit",
			35, 34,
			IDB_BITMAP43,
			hInstance,
			SIZE{ 168,266 }
		)
	{
		pitchTypes.push_back(new AccelBall(3.0f));
	}
	void decideNextPitch()override {
		//���팈��
		currentPitchNumber = 0;
		//����
		setPitchingSpeed(pitchTypes.at(currentPitchNumber)->decideVelocity(*this));
		//�R�[�X
		std::random_device rd;
		std::mt19937 gen(rd()); // �����Z���k�E�c�C�X�^����������
		std::uniform_real_distribution<float> dis2(-10.0f, 5.0f);
		setPitchingCourse(dis2(gen));
		//�㉺�����̏���
		setHVelocity(pitchTypes[currentPitchNumber]->decideHVelocity());
	}
};