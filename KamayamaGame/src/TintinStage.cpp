#include "TintinStage.h"

#include "TintinPitcher.h"
#include "KamayamaBatter.h"
#include "TheHundredAcreWoodStadium.h"

TintinStage::TintinStage():
	Stage(L"TintinStage",
		new TintinPitcher(),
		new KamayamaBatter(),
		new TheHundredAcreWoodStadium(),
		3,
		5)
{
	
}
