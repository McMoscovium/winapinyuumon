#pragma once

#include "PitchType/PitchType.h"

class AccelBall : public PitchType
{
private:
	float accelRate;
	int beginAccelY;//â¡ë¨ÇénÇﬂÇÈYç¿ïW
	float acceleration;
public:
	AccelBall();
	AccelBall(float accel):
		PitchType(L"ACCELBALL"),
		accelRate(accel),
		beginAccelY(309),
		acceleration(2.0f)
	{ }
	~AccelBall() = default;
	void update(Ball& ball, int frame) override;
	float decideAngle() override;
	float decideHVelocity() override { return 0; }
	int decideVelocity(Pitcher& pitcher)override;
};