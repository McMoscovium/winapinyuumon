#include "BatBoundingBox.h"

BatBoundingBox::BatBoundingBox(LPCTSTR path, std::wstring objectName, SIZE frameSize, POINT pos) :
	BoundingBox(path, objectName, frameSize, pos)
{
}

void BatBoundingBox::updateBox(const int currentBatterFrame)
{
}
