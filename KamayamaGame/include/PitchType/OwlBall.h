#pragma once

#include "PitchType.h"

class Pitcher;

class OwlBall : public PitchType
{
private:
	float sharpness = 60.0f;
	char frequency = 2;//frequencyフレームに1回曲がる
public:
	OwlBall():
		PitchType(L"OWLBALL"){ }

	void update(Ball& ball, int frame) override;
	float decideAngle() override;
	float decideHVelocity() override { return 0; }
	int decideVelocity(Pitcher& pitcher)override;
};