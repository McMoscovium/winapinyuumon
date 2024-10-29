#pragma once

#include"GameState.h"

class Game;
class GameOverState;
class InputManager;

class PlayingState :
    public GameState
{
public:
    ~PlayingState()override;
    void update(Game* game,InputManager* inputManager)override;
};

