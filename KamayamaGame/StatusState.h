#pragma once
#include "GameState.h"

class Game;
class InputManager;

class StatusState :
    public GameState
{
public:
    //コンストラクタ
    StatusState();

    void update(Game* game, InputManager* inputManager)override;
};

