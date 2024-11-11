#include "Ball.h"
#include "Vector2D.h"
#include <Windows.h>
#include "Window.h"

Ball::Ball()
{
}



int Ball::getAngle() const
{
	return angle;
}

int Ball::getVelocity() const
{
	return velocity;
}

void Ball::setAngle(const int a)
{
	angle = a;
}

void Ball::setVelocity(const int v)
{
	velocity = v;
}

void Ball::sethVelocity(const int v)
{
	hVelocity = v;
}
