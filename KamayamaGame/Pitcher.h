#pragma once

#include "GameObject.h"

class Pitcher :
	public GameObject
{
public:
	Pitcher(LPCTSTR path, std::wstring objectName, SIZE frameSize);
private:
	//
	void updatePitchingMotion();
};

