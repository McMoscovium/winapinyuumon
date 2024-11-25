#pragma once

#include <string>
#include <memory>
#include "Pitcher.h"
#include "Batter.h"
#include "Stadium.h"



class Stage
{
protected:
	int norm;//ƒmƒ‹ƒ}
	int trials;//‹…”
	
public:
	const std::wstring stageName;
	const std::wstring pitcherName;

	Stage(
		const std::wstring& name,
		const std::wstring& pitcherName,
		int norm,
		int trials
	);
	virtual ~Stage();
	
	const int getNorm()const;
	const int getTrials()const;

	virtual std::unique_ptr<Pitcher> createPitcher() = 0;
	virtual std::unique_ptr<Batter> createBatter() = 0;
	virtual std::unique_ptr<Stadium> createStadium() = 0;
};