#pragma once

#include <string>

class Batter
{
private:
	std::wstring name;
	int power;
	float speed;
	float meet;
public:
	Batter(std::wstring batterName, int power, float speed, int meet);
	virtual ~Batter() = default;

	//
	std::wstring getName()const;
	//
	int getPower()const;
	//
	float getMeet()const;
	//
	float getSpeed()const;
};