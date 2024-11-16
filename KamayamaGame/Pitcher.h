#pragma once

#include <string>
#include <vector>
#include "PitchType.h"
#include "Straight.h"

class Pitcher
{
private:
	std::wstring pitcherName;
	std::vector<PitchType*> pitchTypes;
	PitchType* nextPitch = nullptr;
	int armStrength;
	int pitchingSpeed = 0;
	//�p�x
	float pitchingCourse = 0;
	//���݂̋���̔ԍ�
	int currentPitchNumber = 0;

public:
	Pitcher(std::wstring pitcherName, int armStrength);
	virtual ~Pitcher();

	//
	int getArmStrength()const;
	//
	int getPitchingSpeed()const;
	float getPitchingAngle()const;
	//
	void setPitchingSpeed(int sp);
	//
	void setPitchingCourse(float c);
	//���݂̋�����擾
	PitchType* getPitchType();
	//
	const std::wstring& getName()const;
	
	//���̋���A�����A������R�[�X�������_���Ɍ���
	virtual void decideNextPitch() = 0;
};

