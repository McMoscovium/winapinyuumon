#pragma once
#include <Windows.h>
#include "GameObject.h"

class BoundingBox:
	public GameObject
{
public:
	BoundingBox(LPCTSTR path, std::wstring objectName, SIZE frameSize, POINT pos);
	virtual ~BoundingBox() = default;
	void setPosition(const POINT pos);
private:
	RECT box;
	POINT position = { 0,0 };

	virtual void updateBox(const int currentBatterFrame) = 0;
};
