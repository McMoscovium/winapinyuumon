#pragma once
#include "PictureObject.h"
#include <Windows.h>
#include <string>

class ValueMeterObject :
    public PictureObject
{
private:
    int value = 0;
    const int maxValue = 10;
public:
    ValueMeterObject(LPCTSTR path, std::string objectName, SIZE frameSize, int maxValue);
    virtual ~ValueMeterObject() = default;
    
    void setValue(int val);
    int getValue()const;
};

