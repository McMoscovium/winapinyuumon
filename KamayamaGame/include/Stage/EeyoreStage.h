#pragma once

#include "Stage/Stage.h"
#include "GameObject/Pitcher/EeyorePitcher.h"
#include "GameObject/Batter/KamayamaBatter.h"
#include "GameObject/Stadium/TheHundredAcreWoodStadium.h"

class EeyoreStage :
	public Stage
{
public:
	EeyoreStage();
	~EeyoreStage() = default;

	std::unique_ptr<Pitcher> createPitcher(HINSTANCE hInstance)override {
		return std::make_unique<EeyorePitcher>(hInstance);
	}
	std::unique_ptr<Batter> createBatter(HINSTANCE hInstance, const SaveData& saveData)override {
		return std::make_unique<KamayamaBatter>(hInstance, saveData);
	}
	std::unique_ptr<Stadium> createStadium()override {
		return std::make_unique<TheHundredAcreWoodStadium>();
	}
};