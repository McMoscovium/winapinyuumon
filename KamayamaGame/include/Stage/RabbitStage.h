#pragma once

#include "Stage/Stage.h"
#include "GameObject/Pitcher/Rabbit.h"
#include "GameObject/Batter/KamayamaBatter.h"
#include "GameObject/Stadium/TheHundredAcreWoodStadium.h"

class RabbitStage :
	public Stage
{
public:
	RabbitStage() :
		Stage(L"RabbitStage", L"Rabbit", 3, 7)
	{
	}
	~RabbitStage() = default;
	std::unique_ptr<Pitcher> createPitcher(HINSTANCE hInstance)override {
		return std::make_unique<Rabbit>(hInstance);
	}
	std::unique_ptr<Batter> createBatter(HINSTANCE hInstance, const SaveData& saveData)override {
		return std::make_unique<KamayamaBatter>(hInstance, saveData);
	}
	std::unique_ptr<Stadium> createStadium()override {
		return std::make_unique<TheHundredAcreWoodStadium>();
	}
};