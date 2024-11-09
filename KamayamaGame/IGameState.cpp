#include "IGameState.h"

IGameState::IGameState(Game& game) :game(game)
{
}

const Game& IGameState::getConstGame() const
{
    return game;
}

Game& IGameState::getGame()
{
    return game;
}
