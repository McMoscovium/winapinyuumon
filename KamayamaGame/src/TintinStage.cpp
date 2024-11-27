#include "TintinStage.h"

#include "TintinPitcher.h"
#include "KamayamaBatter.h"
#include "TheHundredAcreWoodStadium.h"


using namespace std;

TintinStage::TintinStage() :
	Stage(L"TintinStage",
		L"tintin",
		3,
		10
		)
{
	
}

std::unique_ptr<Pitcher> TintinStage::createPitcher()
{
	return make_unique<TintinPitcher>();
}

std::unique_ptr<Batter> TintinStage::createBatter()
{
	return make_unique<KamayamaBatter>();
}

std::unique_ptr<Stadium> TintinStage::createStadium()
{
	return make_unique<TheHundredAcreWoodStadium>();
}
