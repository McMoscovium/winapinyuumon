#pragma once

#include "Stage/Stage.h"
#include "GameObject/Pitcher/Piglet.h"
#include "GameObject/Batter/KamayamaBatter.h"
#include "GameObject/Stadium/TheHundredAcreWoodStadium.h"

class PigletStage :
	public Stage
{
public:
	PigletStage():
		Stage(L"PigletStage", L"Piglet", 3, 7, 3, 1.4f)
	{
	}
	~PigletStage() = default;
	std::unique_ptr<Pitcher> createPitcher(HINSTANCE hInstance)override {
		return std::make_unique<Piglet>(hInstance);
	}
	std::unique_ptr<Batter> createBatter(HINSTANCE hInstance, const SaveData& saveData)override {
		return std::make_unique<KamayamaBatter>(hInstance, saveData);
	}
	std::unique_ptr<Stadium> createStadium()override {
		return std::make_unique<TheHundredAcreWoodStadium>();
	}
};