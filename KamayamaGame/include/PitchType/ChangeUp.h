#pragma once

#include "PitchType/PitchType.h"


class Pitcher;

class ChangeUp : public PitchType
{
private:
public:
	ChangeUp() :
		PitchType(L"CHANGEUP") {
	}
	void update(Ball& ball, int frame) override;
	float decideAngle() override;
	float decideHVelocity() override { return 0; }
	int decideVelocity(Pitcher& pitcher)override;
};