#pragma once

#include "GameObject/Pitcher/Pitcher.h"

#include "PitchType/WhiteBall.h"
#include <random>

#include "resource.h"

class KangaRoo :
	public Pitcher
{
private:
public:
	KangaRoo(HINSTANCE hInstance) :
		Pitcher(
			L"kanga",
			20, 34,
			IDB_BITMAP43,
			hInstance,
			SIZE{ 168,266 }
		)
	{
		pitchTypes.push_back(new WhiteBall());
	}
	void decideNextPitch()override {
		//���팈��
		currentPitchNumber = 0;

		//����
		std::random_device rd;
		std::mt19937 gen(rd()); // �����Z���k�E�c�C�X�^����������
		std::uniform_int_distribution<> dis1(int(getArmStrength() * 0.7f), getArmStrength());//��l�m�����z
		setPitchingSpeed(dis1(gen));

		//�R�[�X
		std::uniform_real_distribution<float> dis2(-10.0f, 5.0f);
		setPitchingCourse(dis2(gen));

		//�㉺�����̏���
		setHVelocity(pitchTypes[currentPitchNumber]->decideHVelocity());
	}
};