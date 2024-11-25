#include "Stage.h"

#include "Pitcher.h"
#include "Batter.h"
#include "Stadium.h"

Stage::Stage(
	const std::wstring& name, const std::wstring& pitcherName, int norm, int trials
):
	stageName(name),
	norm(norm),
	trials(trials),
	pitcherName(pitcherName)
{

}

Stage::~Stage()
{
}

const int Stage::getNorm() const
{
	return norm;
}

const int Stage::getTrials() const
{
	return trials;
}