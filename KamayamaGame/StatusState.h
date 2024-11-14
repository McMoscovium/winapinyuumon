#pragma once
#include "GameState.h"
#include "HatimituMeter.h"

class Game;
class InputManager;

class StatusState :
    public GameState<StatusState,GameSubState<StatusState>>
{
private:
    HatimituMeter hatimituMeter;
public:
    //コンストラクタ
    StatusState(Game& game);

    void update(Game& game)override;
};

