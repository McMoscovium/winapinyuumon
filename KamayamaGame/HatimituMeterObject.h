#pragma once
#include "ValueMeterObject.h"
class HatimituMeterObject :
    public ValueMeterObject
{
private:
public:
    HatimituMeterObject(std::string objectName, LPCTSTR path,  SIZE frameSize) :
        ValueMeterObject(path, objectName, frameSize, 20) {}
    ~HatimituMeterObject() = default;

    void render(HDC hdc)const override;
};