#include "GameObject/ValueMeterObject.h"

ValueMeterObject::ValueMeterObject(std::string objectName, int resourceId, HINSTANCE hInstance, SIZE frameSize, int maxValue) :
	PictureObject(objectName, resourceId, hInstance, frameSize), 
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
