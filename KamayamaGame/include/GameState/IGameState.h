#pragma once

#include <unordered_map>
#include "GameObject/GameObject.h"
#include <vector>
#include "GameObject/GameObjectManager.h"
#include "Game/AudioManager.h"

class Game;

class IGameState
{
protected:
    Game& game;//êeã 
    GameObjectManager gameObjectManager;
    AudioManager audioManager;
public:
    IGameState(Game& game);
    virtual ~IGameState();
    virtual void update(Game& game) = 0;

    void showAll();
    Game& getGame();

    GameObjectManager& getGameObjectManager();
    AudioManager& getAudioManager();
};