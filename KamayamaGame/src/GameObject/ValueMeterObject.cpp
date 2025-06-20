#include "GameObject/ValueMeterObject.h"

ValueMeterObject::ValueMeterObject(
	std::string objectName,
	int resourceId,
	HINSTANCE hInstance,
	SIZE frameSize,
	int value,
	int filledValue,
	int maxValue
) :
	PictureObject(objectName, resourceId, hInstance, frameSize), 
	value(value),
	filledValue(filledValue),
	maxValue(maxValue)
{
}

void ValueMeterObject::setValue(int val)
{
	if (val > this->filledValue) {
		OutputDebugString(L"ValueMeterObject::setValueに渡す値が無効です。\n");
		return;
	}
	value = val;
}

int ValueMeterObject::getValue() const
{
	return value;
}
