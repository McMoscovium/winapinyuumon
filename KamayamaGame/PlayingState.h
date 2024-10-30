#pragma once

#include"GameState.h"
#include <unordered_map>
#include "GameObject.h"
#include <string>
#include <vector>

class Game;
class InputManager;
class GameObject;

class PlayingState :
    public GameState
{
public:
    ~PlayingState()override;
    void update(Game* game,InputManager* inputManager)override;
    const std::unordered_map<std::wstring, GameObject*>* getGameObjects()const override;

private:
    std::vector<std::wstring> objectNames;
    std::unordered_map<std::wstring, GameObject*> gameObjects;//GameObject‚Æ‚»‚Ì–¼‘O‚ÌƒyƒA
};