#pragma once

#include "GameState.h"

#include <string>
#include <vector>

class Game;
class InputManager;

class GameOverState :
    public GameState<GameOverState>
{
    using SubStateType = GameSubState<GameOverState>;
public:
    GameOverState(Game& game);
    ~GameOverState()override;
    void update()override;
private:
};