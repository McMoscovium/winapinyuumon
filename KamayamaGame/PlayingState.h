#pragma once

#include"GameState.h"

class Game;
class GameOverState;

class PlayingState :
    public GameState
{
public:
    ~PlayingState()override;
    void update(Game* game)override;
};

