#pragma once

#include <string>
#include <memory>
#include "GameObject/Pitcher/Pitcher.h"
#include "GameObject/Batter/Batter.h"
#include "GameObject/Stadium/Stadium.h"

class SaveData;

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

	virtual std::unique_ptr<Pitcher> createPitcher(HINSTANCE) = 0;
	virtual std::unique_ptr<Batter> createBatter(HINSTANCE, const SaveData&) = 0;
	virtual std::unique_ptr<Stadium> createStadium() = 0;
};