#pragma once

#include "Stage/Stage.h"
#include "GameObject/Pitcher/Lumpy.h"
#include "GameObject/Batter/KamayamaBatter.h"
#include "GameObject/Stadium/TheHundredAcreWoodStadium.h"

class LumpyStage :
	public Stage
{
public:
	LumpyStage():
		Stage(L"LumpyStage", L"Lumpy", 3, 7)
	{
	}
	~LumpyStage() = default;
	std::unique_ptr<Pitcher> createPitcher(HINSTANCE hInstance)override {
		return std::make_unique<Lumpy>(hInstance);
	}
	std::unique_ptr<Batter> createBatter(HINSTANCE hInstance, const SaveData& saveData)override {
		return std::make_unique<KamayamaBatter>(hInstance, saveData);
	}
	std::unique_ptr<Stadium> createStadium()override {
		return std::make_unique<TheHundredAcreWoodStadium>();
	}
};