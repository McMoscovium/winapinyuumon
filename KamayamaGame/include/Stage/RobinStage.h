#pragma once

#include "Stage/Stage.h"
#include "GameObject/Pitcher/Robin.h"
#include "GameObject/Batter/KamayamaBatter.h"
#include "GameObject/Stadium/TheHundredAcreWoodStadium.h"

class RobinStage :
	public Stage
{
public:
	RobinStage():
		Stage(L"RobinStage",L"Robin", 3, 7){ }

	~RobinStage() = default;

	std::unique_ptr<Pitcher> createPitcher(HINSTANCE hInstance)override {
		return std::make_unique<Robin>(hInstance);
	}
	std::unique_ptr<Batter> createBatter(HINSTANCE hInstance, const SaveData& saveData)override {
		return std::make_unique<KamayamaBatter>(hInstance, saveData);
	}
	std::unique_ptr<Stadium> createStadium()override {
		return std::make_unique<TheHundredAcreWoodStadium>();
	}
};