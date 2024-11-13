#pragma once

#include "PlayingState.h"
#include <Windows.h>

class Stadium
{
public:
	Stadium() {}
	virtual ~Stadium() = default;

	virtual PlayingState::FlyBallResult result(POINT pos) = 0;
};

