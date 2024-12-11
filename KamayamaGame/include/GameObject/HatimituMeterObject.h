#pragma once
#include "GameObject/ValueMeterObject.h"
class HatimituMeterObject :
    public ValueMeterObject
{
private:
public:
    HatimituMeterObject(std::string objectName, int resourceId, HINSTANCE hInstance, SIZE frameSize) :
        ValueMeterObject(objectName, resourceId, hInstance,  frameSize, 20) {}
    ~HatimituMeterObject() = default;

    void render(HDC hdc)const override;
};