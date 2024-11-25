#include "SasakiStage.h"

#include "SasakiPitcher.h"
#include "KamayamaBatter.h"
#include "TheHundredAcreWoodStadium.h"

using namespace std;

SasakiStage::SasakiStage():
	Stage(L"SasakiStage",
		L"²X–Ø˜NŠó",
		3,
		5
	)
{
}

std::unique_ptr<Pitcher> SasakiStage::createPitcher()
{
	return make_unique<SasakiPitcher>();
}

std::unique_ptr<Batter> SasakiStage::createBatter()
{
	return make_unique<KamayamaBatter>();
}

std::unique_ptr<Stadium> SasakiStage::createStadium()
{
	return make_unique<TheHundredAcreWoodStadium>();
}
