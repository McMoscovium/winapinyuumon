#pragma once

#include "Stage/Stage.h"
#include "GameObject/Pitcher/Tigger.h"
#include "GameObject/Batter/KamayamaBatter.h"
#include "GameObject/Stadium/TheHundredAcreWoodStadium.h"

class TiggerStage :
	public Stage
{
public:
	TiggerStage():
		Stage(L"TiggerStage", L"Tigger", 3, 7)
	{
	}
	~TiggerStage() = default;
	std::unique_ptr<Pitcher> createPitcher(HINSTANCE hInstance)override {
		return std::make_unique<Tigger>(hInstance);
	}
	std::unique_ptr<Batter> createBatter(HINSTANCE hInstance, const SaveData& saveData)override {
		return std::make_unique<KamayamaBatter>(hInstance, saveData);
	}
	std::unique_ptr<Stadium> createStadium()override {
		return std::make_unique<TheHundredAcreWoodStadium>();
	}
};