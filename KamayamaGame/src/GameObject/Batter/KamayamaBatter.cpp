#include"GameOBject/Batter/KamayamaBatter.h"
#include "resource.h"
#include "Game/SaveData/SaveData.h"

using namespace std;

KamayamaBatter::KamayamaBatter(HINSTANCE hInstance, const SaveData& saveData) :
	Batter(
		(L"kamayama"),
		25,//�p���[
		4.0f,//�X�s�[�h
		50,//�~�[�g
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
