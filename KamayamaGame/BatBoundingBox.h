#pragma once
#include "BoundingBox.h"

#include <Windows.h>

class BatBoundingBox :
    public BoundingBox
{
public:
    BatBoundingBox(LPCTSTR path, std::wstring objectName, SIZE frameSize, POINT pos);
private:
    void updateBox(const int currentBatterFrame)override;
};

