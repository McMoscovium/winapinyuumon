#include "GameObject/Ball.h"
#include "util/Vector2D.h"
#include <Windows.h>
#include "Game/Window.h"
#include <cmath>
#include <numbers>

void Ball::updateByPitchType(Pitcher* pitcher)
{
	framesSinceReleased++;
	pitcher->getPitchType()->update(*this, framesSinceReleased);
}

Ball::Ball() :
	position({ 529,162 })
{
}



float Ball::getAngle() const
{
	return angle;
}

int Ball::getVelocity() const
{
	return velocity;
}

float Ball::getHVelocity() const
{
	return hVelocity;
}

float Ball::getHeight() const
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

float Ball::getGravity() const
{
	return gravity;
}

void Ball::setAngle(const float a)
{
	angle = a;
}

void Ball::setVelocity(const int v)
{
	velocity = v;
}

void Ball::sethVelocity(const float v)
{
	hVelocity = v;
}

void Ball::setPosition(POINT pos)
{
	position = pos;
}


void Ball::setHeight(float h)
{
	height = h;
}

void Ball::resetFrame()
{
	framesSinceReleased = 0;
}

POINT Ball::updatePitch(Pitcher* pitcher)
{
	//球種に合わせて次のvelocityの更新
	updateByPitchType(pitcher);
	//ボールのゲーム内位置の更新
	const POINT formerPos = getPosition();
	LONG movementX = (LONG)std::round(getVelocity() * std::sin(std::numbers::pi * getAngle() / 180));
	LONG movementY= -(LONG)std::round(getVelocity() * std::cos(getAngle() * std::numbers::pi / 180));
	LONG movementZ = (LONG)std::round(getHVelocity());
	setPosition({
		formerPos.x + movementX,
		formerPos.y + movementY
		});
	setHeight(getHeight() + movementZ);
	return getPosition();
}
