#include"GameOBject/Batter/KamayamaBatter.h"
#include "resource.h"
#include "Game/SaveData/SaveData.h"

using namespace std;

KamayamaBatter::KamayamaBatter(HINSTANCE hInstance, const SaveData& saveData) :
	Batter(
		(L"kamayama"),
		25,//パワー
		4.0f,//スピード
		50,//ミート
		IDB_BITMAP41,
		hInstance,
		SIZE{ 360,391 }
	)
{
	char powerMeter = saveData.getPower();
	char meetMeter = saveData.getMeet();
	char speedMeter = saveData.getSpeed();
	Skill skill = saveData.getSkill();
	power += powerMeter;
	meet += (int)(meetMeter * 1.6);
	speed += (float)speedMeter / 2;
	KamayamaBatter::skill = skill;
}
