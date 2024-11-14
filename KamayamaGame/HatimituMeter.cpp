#include "HatimituMeter.h"

HatimituMeterObject* HatimituMeter::getObjPtr()
{
    return object;
}

void HatimituMeter::setValue(int v)
{
    object->setValue(v);
    return;
}
