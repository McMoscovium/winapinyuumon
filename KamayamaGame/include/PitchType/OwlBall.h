#pragma once

#include "PitchType.h"

class OwlBall : public PitchType
{
private:
	float sharpness = 60.0f;
	char frequency = 2;//frequency�t���[����1��Ȃ���
public:
	OwlBall():
		PitchType(L"OWLBALL"){ }

	void update(Ball& ball, int frame) override;
	float decideAngle() override;
	float decideHVelocity() override { return 0; }
};