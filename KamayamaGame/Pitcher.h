#pragma once

#include <string>
#include <vector>
#include "PitchType.h"
#include "Straight.h"

class Pitcher
{
private:
	std::wstring pitcherName;
	std::vector<PitchType> pitchTypes = { Straight() };
	PitchType& nextPitch = pitchTypes.at(0);
	int armStrength;
	int pitchingSpeed = 0;
	int pitchingCourse = 0;
public:
	Pitcher(std::wstring pitcherName, int armStrength);
	virtual ~Pitcher() = default;

	//
	int getArmStrength()const;
	//
	void setPitchingSpeed(int sp);
	//
	void setPitchingCourse(int c);
	
	//���̋���A�����A������R�[�X�������_���Ɍ���
	virtual void decideNextPitch() = 0;
};

