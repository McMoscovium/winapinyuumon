#pragma once

#include "GameState.h"

class Game;

class GameOverState :
    public GameState
{
public:
    void update(Game* game)override;
};