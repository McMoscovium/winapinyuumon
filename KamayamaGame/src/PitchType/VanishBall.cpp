#include "PitchType/VanishBall.h"

#include "GameObject/Ball.h"
#include <random>

VanishBall::VanishBall():
	PitchType(L"VanishBall"),
	vanishY(320)
{
}

void VanishBall::update(Ball& ball, int frame)
{
	int Y = ball.getY();;
	if (Y < vanishY)return;

	//Y‚ªvanishY‚ð’´‚¦‚½‚çÁ‚¦‚é
	ball.vanish();
	return;
}

float VanishBall::decideAngle()
{
	return 0.0f;
}
