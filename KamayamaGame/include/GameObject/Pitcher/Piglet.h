#pragma once

#include "GameObject/Pitcher/Pitcher.h"

#include "PitchType/Straight.h"
#include <random>

#include "resource.h"

class Piglet :
	public Pitcher
{
private:
public:
	Piglet(HINSTANCE hInstance) :
		Pitcher(
			L"piglet",
			30, 34,
			IDB_BITMAP43,
			hInstance,
			SIZE{ 168,266 }
		)
	{
		pitchTypes.push_back(new Straight());
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
		std::uniform_real_distribution<float> dis2(-9.0f, 3.0f);
		setPitchingCourse(dis2(gen));
		//�㉺�����̏���
		setHVelocity(pitchTypes[currentPitchNumber]->decideHVelocity());
	}
};