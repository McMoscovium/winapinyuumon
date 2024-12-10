#include "IGameState.h"

#include "PictureObject.h"

IGameState::IGameState(Game& game):
    game(game)
{
}

IGameState::~IGameState()
{
}

void IGameState::showAll()
{
    for (auto& obj : gameObjectManager.getDrawOrder()) {
        obj.get().appear();
    }
}

Game& IGameState::getGame()
{
    return game;
}

GameObjectManager& IGameState::getGameObjectManager()
{
    return gameObjectManager;
}

AudioManager& IGameState::getAudioManager()
{
    return audioManager;
}
