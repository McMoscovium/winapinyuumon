#include "Result.h"
#include <algorithm>

void Result::addRun() {
	runs++;
}

void Result::updateMaxDistance(int dist)
{
	maxDistance = std::max<int>(maxDistance, dist);
	return;
}

void Result::addSuccessiveRuns()
{
	successiveRuns++;
}

void Result::resetSuccessiveRuns()
{
	successiveRuns = 0;
}

void Result::updateMaxSuccessiveRuns()
{
	maxSuccessiveRuns = std::max<int>(maxSuccessiveRuns, successiveRuns);
	return;
}

void Result::addDistanceSum(int dist)
{
	distanceSum += dist;
}

int Result::calculateScore(int dist) const
{
	return dist;
}

void Result::addScore(int score)
{
	Result::score += score;
}

void Result::update(int dist, bool isRun)
{
	if (isRun) {
		addRun();
		addSuccessiveRuns();
		updateMaxSuccessiveRuns();
	}
	else {
		resetSuccessiveRuns();
	}

	updateMaxDistance(dist);
	updateMaxSuccessiveRuns();
	addDistanceSum(dist);

	int score = calculateScore(dist);
	addScore(score);
}

bool Result::isClear() const
{
	return runs >= norm;
}

int Result::getRuns() const
{
	return runs;
}

int Result::getMaxSuccessiveRuns() const
{
	return maxSuccessiveRuns;
}

int Result::getMaxDistance() const
{
	return maxDistance;
}

int Result::getDistanceSum() const
{
	return distanceSum;
}
