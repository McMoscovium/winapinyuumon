#include "SasakiStage.h"

#include "SasakiPitcher.h"
#include "KamayamaBatter.h"
#include "TheHundredAcreWoodStadium.h"

SasakiStage::SasakiStage():
	Stage(L"SasakiStage",
		new SasakiPitcher(),
		new KamayamaBatter(),
		new TheHundredAcreWoodStadium(),
		3,
		5)
{
}
