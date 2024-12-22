#include "Stage/SasakiStage.h"

#include "GameObject/Pitcher/SasakiPitcher.h"
#include "GameObject/Batter/KamayamaBatter.h"
#include "GameObject/Stadium/TheHundredAcreWoodStadium.h"
#include "Game/SaveData/SaveData.h"

using namespace std;

SasakiStage::SasakiStage():
	Stage(L"SasakiStage",
		L"ç≤ÅXñÿòNäÛ",
		3,
		5,
		10,
		1.0f
	)
{
}

std::unique_ptr<Pitcher> SasakiStage::createPitcher(HINSTANCE hInstance)
{
	return make_unique<SasakiPitcher>(hInstance);
}

std::unique_ptr<Batter> SasakiStage::createBatter(HINSTANCE hInstance, const SaveData& saveData)
{
	return std::make_unique<KamayamaBatter>(hInstance, saveData);
}


std::unique_ptr<Stadium> SasakiStage::createStadium()
{
	return make_unique<TheHundredAcreWoodStadium>();
}
