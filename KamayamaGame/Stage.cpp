#include "Stage.h"

#include "Pitcher.h"
#include "Batter.h"
#include "Stadium.h"

Stage::Stage(std::wstring name, Pitcher* pitcher, Batter* batter, Stadium* stadium, int norm, int trials):
	stageName(name),
	norm(norm),
	trials(trials),
	pitcher(pitcher),
	batter(batter),
	stadium(stadium)
{
}

Stage::~Stage()
{
	if (pitcher) {
		delete pitcher;
		pitcher = nullptr;
	}
	if (batter) {
		delete batter;
		batter = nullptr;
	}
	if (stadium) {
		delete stadium;
		stadium = nullptr;
	}
}

const int Stage::getNorm() const
{
	return norm;
}

const int Stage::getTrials() const
{
	return trials;
}

Pitcher* Stage::getPitcher()
{
	return pitcher;
}

Batter* Stage::getBatter()
{
	return batter;
}

Stadium* Stage::getStadium()
{
	return stadium;
}
