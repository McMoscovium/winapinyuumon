#pragma once
#include "HatimituMeterObject.h"

class HatimituMeter
{
private:
	HatimituMeterObject* object;

public:
	HatimituMeter() :
		object(new HatimituMeterObject(L".//assets//�͂��݂�.bmp", L"HATIMITUMETER", { 49,45 })) {}
	~HatimituMeter() {
		OutputDebugString(L"HatimituMeter�̃f�X�g���N�^���Ă΂ꂽ\n");
	}
	HatimituMeterObject* getObjPtr();
	void setValue(int v);
};

