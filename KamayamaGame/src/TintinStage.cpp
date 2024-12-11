#include "Stage/TintinStage.h"

#include "GameObject/Pitcher/TintinPitcher.h"
#include "GameObject/Batter/KamayamaBatter.h"
#include "GameObject/Stadium/TheHundredAcreWoodStadium.h"


using namespace std;

TintinStage::TintinStage() :
	Stage(L"TintinStage",
		L"tintin",
		3,
		10
		)
{
	
}

std::unique_ptr<Pitcher> TintinStage::createPitcher(HINSTANCE hInstance)
{
	return make_unique<TintinPitcher>(hInstance);
}

std::unique_ptr<Batter> TintinStage::createBatter(HINSTANCE hInstance)
{
	return make_unique<KamayamaBatter>(hInstance);
}

std::unique_ptr<Stadium> TintinStage::createStadium()
{
	return make_unique<TheHundredAcreWoodStadium>();
}
