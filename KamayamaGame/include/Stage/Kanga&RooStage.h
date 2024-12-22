#pragma once

#include "Stage/Stage.h"
#include "GameObject/Pitcher/Kanga&Roo.h"
#include "GameObject/Batter/KamayamaBatter.h"
#include "GameObject/Stadium/TheHundredAcreWoodStadium.h"

class KangaRooStage :
	public Stage
{
public:
	KangaRooStage():
		Stage(L"KangaRooStage", L"Kanga&Roo", 3, 7, 4, 1.4f)
	{
	}
	~KangaRooStage() = default;
	std::unique_ptr<Pitcher> createPitcher(HINSTANCE hInstance)override {
		return std::make_unique<KangaRoo>(hInstance);
	}
	std::unique_ptr<Batter> createBatter(HINSTANCE hInstance, const SaveData& saveData)override {
		return std::make_unique<KamayamaBatter>(hInstance, saveData);
	}
	std::unique_ptr<Stadium> createStadium()override {
		return std::make_unique<TheHundredAcreWoodStadium>();
	}
};