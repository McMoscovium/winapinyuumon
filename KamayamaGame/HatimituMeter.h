#pragma once
#include "HatimituMeterObject.h"

class HatimituMeter
{
private:
	HatimituMeterObject* object;

public:
	HatimituMeter() :
		object(new HatimituMeterObject(L".//assets//はちみつ.bmp", L"HATIMITUMETER", { 49,45 })) {}
	~HatimituMeter() {
		OutputDebugString(L"HatimituMeterのデストラクタが呼ばれた\n");
	}
	HatimituMeterObject* getObjPtr();
	void setValue(int v);
};

