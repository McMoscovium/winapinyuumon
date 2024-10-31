#pragma once

#include "GameState.h"

#include <string>
#include <vector>

class Game;
class InputManager;

class GameOverState :
    public GameState
{
public:
    GameOverState();
    ~GameOverState()override;
    void update(Game* game,InputManager* inputManager)override;

private:
};