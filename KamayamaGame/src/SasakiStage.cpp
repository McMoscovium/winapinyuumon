#include "Stage/SasakiStage.h"

#include "GameObject/Pitcher/SasakiPitcher.h"
#include "GameObject/Batter/KamayamaBatter.h"
#include "GameObject/Stadium/TheHundredAcreWoodStadium.h"

using namespace std;

SasakiStage::SasakiStage():
	Stage(L"SasakiStage",
		L"ç≤ÅXñÿòNäÛ",
		3,
		5
	)
{
}

std::unique_ptr<Pitcher> SasakiStage::createPitcher(HINSTANCE hInstance)
{
	return make_unique<SasakiPitcher>(hInstance);
}

std::unique_ptr<Batter> SasakiStage::createBatter(HINSTANCE hInstance)
{
	return make_unique<KamayamaBatter>(hInstance);
}

std::unique_ptr<Stadium> SasakiStage::createStadium()
{
	return make_unique<TheHundredAcreWoodStadium>();
}
