#include "BoundingBox.h"

#include <Windows.h>

BoundingBox::BoundingBox(LPCTSTR path, std::wstring objectName, SIZE frameSize, POINT pos) :
	GameObject(path, objectName, frameSize),
	box({ pos.x,pos.y,pos.x + frameSize.cx,pos.y + frameSize.cy })
{
}

void BoundingBox::setPosition(const POINT pos)
{
	position = pos;
}
