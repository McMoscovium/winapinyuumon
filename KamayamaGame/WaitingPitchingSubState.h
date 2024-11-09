#pragma once
#include "GameSubState.h"
#include "PlayingState.h"
#include <Windows.h>
#include "Timer.h"

class WaitingPitchingSubState :
    public GameSubState<PlayingState>
{
public:
    WaitingPitchingSubState(PlayingState& context);
    void update()override;
private:
    Timer timer;
};