#include "Pitcher.h"

#include "Straight.h"

Pitcher::Pitcher(std::wstring pitcherName, int armStrength) :
	pitcherName(pitcherName),
	armStrength(armStrength)
{
	pitchTypes.push_back(new Straight());
}

Pitcher::~Pitcher()
{
	for (auto& type : pitchTypes) {
		if (type) {
			delete type;
			type = nullptr;
		}
	}
}

int Pitcher::getArmStrength() const
{
	return armStrength;
}

int Pitcher::getPitchingSpeed() const
{
	return pitchingSpeed;
}

float Pitcher::getPitchingAngle() const
{
	return pitchingCourse;
}

void Pitcher::setPitchingSpeed(int sp)
{
	pitchingSpeed = sp;
}

void Pitcher::setPitchingCourse(float c)
{
	pitchingCourse = c;
}

PitchType* Pitcher::getPitchType()
{
	return pitchTypes.at(currentPitchNumber);
}

const std::wstring& Pitcher::getName() const
{
	return pitcherName;
}
