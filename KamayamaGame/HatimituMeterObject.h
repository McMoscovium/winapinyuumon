#pragma once
#include "ValueMeterObject.h"
class HatimituMeterObject :
    public ValueMeterObject
{
private:
public:
    HatimituMeterObject(LPCTSTR path, std::wstring objectName, SIZE frameSize) :
        ValueMeterObject(path, objectName, frameSize, 20) {}
    ~HatimituMeterObject() = default;

    void render(HDC hdc)const override;
};