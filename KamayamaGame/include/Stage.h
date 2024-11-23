#pragma once

#include <string>

class Pitcher;
class Stadium;
class Batter;

class Stage
{
private:
	std::wstring stageName;
	int norm;//ƒmƒ‹ƒ}
	int trials;//‹…”
	Pitcher* pitcher;//‘Šè“Šè
	Batter* batter;
	Stadium* stadium;//‹…ê
	
public:
	Stage(
		std::wstring name,
		Pitcher* pitcher,
		Batter* batter,
		Stadium* stadium,
		int norm,
		int trials,
		const std::wstring& pitcherPath,
		const std::wstring& batterPath
	);
	virtual ~Stage();

	const int getNorm()const;
	const int getTrials()const;
	Pitcher* getPitcher();
	Batter* getBatter();
	Stadium* getStadium();
	const std::wstring pitcherPath;
	const std::wstring batterPath;
};

