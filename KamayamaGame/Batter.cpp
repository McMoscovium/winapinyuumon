#include "Batter.h"

Batter::Batter(std::wstring batterName, int power, float speed, int meet):
	name(batterName),
	power(power),
	speed(speed),
	meet(meet)
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
