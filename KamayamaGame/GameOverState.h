#pragma once

#include "GameState.h"
#include "GameSubState.h"

#include <string>
#include <vector>

class Game;
class InputManager;

class GameOverState :
    public GameState<GameOverState,GameSubState<GameOverState>>
{
public:
    GameOverState(Game& game);
    void update(Game& game)override;
private:
};