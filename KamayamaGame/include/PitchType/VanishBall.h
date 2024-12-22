#pragma once
#include "PitchType/PitchType.h"

class Pitcher;

class VanishBall : public PitchType
{
private:
	int vanishY;
public:
	VanishBall();
	~VanishBall() = default;
	void update(Ball& ball, int frame) override;
	virtual float decideAngle() override;
	virtual float decideHVelocity() override { return 0; }
	int decideVelocity(Pitcher& pitcher)override;
};