#pragma once

#include "GameState.h"

class Game;
class InputManager;

class GameOverState :
    public GameState
{
public:
    void update(Game* game,InputManager* inputManager)override;
};