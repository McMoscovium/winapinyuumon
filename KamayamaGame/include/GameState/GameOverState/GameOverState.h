#pragma once

#include "GameState/GameState.h"
#include "GameState/GameSubState.h"

#include <string>
#include <vector>

class Game;
class InputManager;

class GameOverState :
    public GameState<GameOverState,GameSubState<GameOverState>>
{
public:
    GameOverState(Game& game, AudioManager& audioManager);
    void update(Game& game)override;
private:
};