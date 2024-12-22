#pragma once

#include "GameObject/Pitcher/Pitcher.h"

#include "PitchType/ChangeUp.h"
#include "PitchType/Straight.h"
#include "PitchType/WhiteBall.h"
#include "PitchType/AccelBall.h"
#include "PitchType/OwlBall.h"
#include "PitchType/VanishBall.h"

#include <random>

#include "resource.h"

class Robin :
	public Pitcher
{
private:
public:
	Robin(HINSTANCE hInstance) :
		Pitcher(
			L"Robin",
			35, 34,
			IDB_BITMAP43,
			hInstance,
			SIZE{ 168,266 }
		)
	{
		pitchTypes.push_back(new ChangeUp());
		pitchTypes.push_back(new Straight(1.3f));
		pitchTypes.push_back(new Straight());
		pitchTypes.push_back(new WhiteBall());
		pitchTypes.push_back(new AccelBall(4.0f));
		pitchTypes.push_back(new OwlBall());
		pitchTypes.push_back(new VanishBall());
	}

	void decideNextPitch()override {
		std::random_device rd;
		std::mt19937 gen(rd()); // �����Z���k�E�c�C�X�^����������

		//���팈��
		std::uniform_int_distribution<> dis1(0, (int)pitchTypes.size()-1);
		currentPitchNumber = dis1(gen);

		//����
		setPitchingSpeed(pitchTypes.at(currentPitchNumber)->decideVelocity(*this));
		//�R�[�X
		setPitchingCourse(pitchTypes[currentPitchNumber]->decideAngle());
		//�㉺�����̏���
		setHVelocity(pitchTypes[currentPitchNumber]->decideHVelocity());
	}
};