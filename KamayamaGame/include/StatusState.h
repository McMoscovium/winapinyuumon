#pragma once
#include "GameState.h"
#include "HatimituMeter.h"
#include "PictureObject.h"

class Game;
class InputManager;

class StatusState :
    public GameState<StatusState,GameSubState<StatusState>>
{
private:
public:
    //コンストラクタ
    StatusState(Game& game);

    void update(Game& game)override;
};

