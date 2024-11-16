#pragma once

#include <string>

class Pitcher;
class Stadium;
class Batter;

class Stage
{
private:
	std::wstring stageName;
	int norm;//�m���}
	int trials;//����
	Pitcher* pitcher;//���蓊��
	Batter* batter;
	Stadium* stadium;//����
	
public:
	Stage(std::wstring name, Pitcher* pitcher, Batter* batter, Stadium* stadium, int norm, int trials);
	virtual ~Stage();

	const int getNorm()const;
	const int getTrials()const;
	Pitcher* getPitcher();
	Batter* getBatter();
	Stadium* getStadium();
};

