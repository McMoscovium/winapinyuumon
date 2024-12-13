#pragma once
#include "GameObject/PictureObject.h"
#include <Windows.h>
#include <string>

class ValueMeterObject :
    public PictureObject
{
private:
    int value = 0;
    int filledValue;//valueÇÇ«Ç±Ç‹Ç≈ëùÇ‚ÇπÇÈÇ©
    const int maxValue;
public:
    ValueMeterObject(
        std::string objectName,
        int resourceId,
        HINSTANCE hInstance,
        SIZE frameSize,
        int value,
        int filledValue,
        int maxValue
    );
    virtual ~ValueMeterObject() = default;
    
    void setValue(int val);
    void addValue() {
        if (value == maxValue) {
            //Ç±ÇÍà»è„ëùÇ‚ÇπÇ»Ç¢
            return;
        }
        if (value == filledValue) {
            //filledValueÇ‡ëùÇ‚Ç∑
            value++;
            filledValue++;
            return;
        }
        value++;
        return;
    }
    void subtractValue() {
        if (value <=1) {
            return;
        }
        value--;
    }
    int getValue()const;
    int getFilledValue()const {
        return filledValue;
    }
};

