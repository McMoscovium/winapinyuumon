#pragma once
#include "GameSubState.h"

#include <memory>

class PlayingState;

class InPitchingSubState :
    public GameSubState<PlayingState>
{
public:
    InPitchingSubState(PlayingState& context);
    void update()override;
private:
    //ピッチングモーションの更新
    void updatePitchingMotion();
};