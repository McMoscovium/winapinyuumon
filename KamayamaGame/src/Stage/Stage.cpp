#include "Stage/Stage.h"

#include "GameObject/Pitcher/Pitcher.h"
#include "GameObject/Batter/Batter.h"
#include "GameObject/Stadium/Stadium.h"

Stage::Stage(
	const std::wstring& name, const std::wstring& pitcherName, int norm, int trials, char stageNumber, float scoreFactor
):
	stageName(name),
	norm(norm),
	trials(trials),
	pitcherName(pitcherName),
	stageNumber(stageNumber),
	scoreFactor(scoreFactor)
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