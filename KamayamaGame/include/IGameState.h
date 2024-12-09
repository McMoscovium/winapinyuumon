#pragma once

#include <unordered_map>
#include "GameObject.h"
#include <vector>
#include "GameObjectManager.h"
#include "AudioManager.h"

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
};