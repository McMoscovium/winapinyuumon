#pragma once

#include <unordered_map>
#include "GameObject.h"
#include <vector>
#include "GameObjectManager.h"

class Game;

class IGameState
{
protected:
    Game& game;//êeã 
    GameObjectManager gameObjectManager;
public:
    IGameState(Game& game);
    virtual ~IGameState();
    virtual void update(Game& game) = 0;

    void showAll();
    Game& getGame();

    GameObjectManager& getGameObjectManager();
};