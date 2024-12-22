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

int VanishBall::decideVelocity(Pitcher& pitcher) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis2(int(pitcher.getArmStrength() * 0.5f), pitcher.getArmStrength());//ˆê—lŠm—¦•ª•z
	return dis2(gen);
}