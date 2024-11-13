#pragma once

#include <string>

class Batter
{
private:
	std::wstring batterName;
	int power;
	int speed;
	int meet;
public:
	Batter(std::wstring batterName, int power, int speed, int meet);
	virtual ~Batter() = default;
};