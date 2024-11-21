#include "ValueMeterObject.h"

ValueMeterObject::ValueMeterObject(LPCTSTR path, std::string objectName, SIZE frameSize,int maxValue) :
	PictureObject(objectName, path, frameSize),
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
