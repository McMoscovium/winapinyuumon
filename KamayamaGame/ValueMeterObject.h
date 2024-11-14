#pragma once
#include "GameObject.h"
#include <Windows.h>
#include <string>

class ValueMeterObject :
    public GameObject
{
private:
    int value = 0;
    const int maxValue = 10;
public:
    ValueMeterObject(LPCTSTR path, std::wstring objectName, SIZE frameSize, int maxValue);
    virtual ~ValueMeterObject() = default;
    
    void setValue(int val);
    int getValue()const;
};

