#pragma once
#include "GameObject/ValueMeterObject.h"
class HatimituMeterObject :
    public ValueMeterObject
{
private:
    char width = 15;//横に何個並べるか
    const int gap = 5;//各はちみつのすき間は5ピクセル開ける
public:
    HatimituMeterObject(
        std::string objectName,
        int resourceId,
        HINSTANCE hInstance,
        SIZE frameSize,
        int value,
        int filledValue
    ) :
        ValueMeterObject(
            objectName,
            resourceId,
            hInstance,
            frameSize,
            value,
            filledValue,
            30
        )
    {}
    ~HatimituMeterObject() = default;

    void render(HDC hdc)const override;
};