#include "Pitcher.h"

Pitcher::Pitcher(std::wstring pitcherName, int armStrength) :
	pitcherName(pitcherName),
	armStrength(armStrength)
{}

int Pitcher::getArmStrength() const
{
	return armStrength;
}

void Pitcher::setPitchingSpeed(int sp)
{
	pitchingSpeed = sp;
}

void Pitcher::setPitchingCourse(int c)
{
	pitchingCourse = c;
}
