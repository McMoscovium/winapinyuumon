#include "ValueMeterObject.h"

ValueMeterObject::ValueMeterObject(LPCTSTR path, std::wstring objectName, SIZE frameSize,int maxValue) :
	GameObject(path, objectName, frameSize),
	maxValue(maxValue)
{
}

void ValueMeterObject::setValue(int val)
{
	value = val;
}

int ValueMeterObject::getValue() const
{
	return value;
}
