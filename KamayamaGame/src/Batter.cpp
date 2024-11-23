#include "Batter.h"

Batter::Batter(const std::wstring& batterName, int power, float speed, int meet, const std::wstring& path, const SIZE& frameSize) :
	name(batterName),
	power(power),
	speed(speed),
	meet(meet),
	path(path),
	frameSize(frameSize)
{
}

std::wstring Batter::getName() const
{
	return name;
}

int Batter::getPower() const
{
	return power;
}

float Batter::getMeet() const
{
	return meet;
}

float Batter::getSpeed() const
{
	return speed;
}
