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
    Game& game;//�e��
    GameObjectManager gameObjectManager;
    AudioManager& audioManager;
public:
    IGameState(Game& game, AudioManager& audioManager);
    virtual ~IGameState();

    virtual void update(Game& game) = 0;
    virtual void enter(Game& game) = 0;
	virtual void exit(Game& game) = 0;

    void showAll();
    Game& getGame();

    GameObjectManager& getGameObjectManager();
    AudioManager& getAudioManager();
};