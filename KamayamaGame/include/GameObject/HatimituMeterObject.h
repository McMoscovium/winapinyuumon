#pragma once
#include "GameObject/ValueMeterObject.h"
class HatimituMeterObject :
    public ValueMeterObject
{
private:
    char width = 15;//���ɉ����ׂ邩
    const int gap = 5;//�e�͂��݂̂����Ԃ�5�s�N�Z���J����
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