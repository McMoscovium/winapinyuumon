#pragma once
#include "HatimituMeterObject.h"

class HatimituMeter
{
private:
	HatimituMeterObject* object;

public:
	HatimituMeter() :
		object(new HatimituMeterObject(L".//assets//�͂��݂�.bmp", L"HATIMITUMETER", { 49,45 })) {}
	~HatimituMeter() {}
	HatimituMeterObject* getObjPtr();
	void setValue(int v);
};

