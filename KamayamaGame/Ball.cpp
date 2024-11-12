#include "Ball.h"
#include "Vector2D.h"
#include <Windows.h>
#include "Window.h"

Ball::Ball() :
	position({ 529,162 })
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

int Ball::getHVelocity() const
{
	return hVelocity;
}

int Ball::getHeight() const
{
	return height;
}

POINT Ball::getPosition() const
{
	return position;
}

LONG Ball::getX() const
{
	return position.x;
}

LONG Ball::getY() const
{
	return position.y;
}

int Ball::getRadius() const
{
	return radius;
}

int Ball::getGravity() const
{
	return gravity;
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

void Ball::setPosition(POINT pos)
{
	position = pos;
}

void Ball::setHeight(int h)
{
	height = h;
}
