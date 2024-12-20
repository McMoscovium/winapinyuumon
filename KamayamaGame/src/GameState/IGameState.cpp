#include "GameState/IGameState.h"

#include "GameObject/PictureObject.h"

IGameState::IGameState(Game& game, AudioManager& audioManager):
    game(game),
	audioManager(audioManager)
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
