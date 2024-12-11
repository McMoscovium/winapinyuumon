#pragma once
#include "GameObject/PictureObject.h"
#include <Windows.h>
#include <string>

class ValueMeterObject :
    public PictureObject
{
private:
    int value = 0;
    const int maxValue = 10;
public:
    ValueMeterObject(std::string objectName, int resourceId,HINSTANCE hInstance,  SIZE frameSize, int maxValue);
    virtual ~ValueMeterObject() = default;
    
    void setValue(int val);
    int getValue()const;
};

