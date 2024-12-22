#pragma once

#include "Stage/Stage.h"

#include "GameObject/Pitcher/OwlPitcher.h"
#include "GameObject/Batter/KamayamaBatter.h"
#include "GameObject/Stadium/TheHundredAcreWoodStadium.h"

class OwlStage : public Stage
{
private:
public:
	OwlStage():
		Stage(
			L"OwlStage",
			L"Owl",
			5,
			10,
			6,
			2.0f
		)
	{
	}

	std::unique_ptr<Pitcher> createPitcher(HINSTANCE hInstance) override
	{
		return std::make_unique<OwlPitcher>(hInstance);
	}

	std::unique_ptr<Batter> createBatter(HINSTANCE hInstance, const SaveData& saveData) override
	{
		return std::make_unique<KamayamaBatter>(hInstance, saveData);
	}

	std::unique_ptr<Stadium> createStadium() override
	{
		return std::make_unique<TheHundredAcreWoodStadium>();
	}
};