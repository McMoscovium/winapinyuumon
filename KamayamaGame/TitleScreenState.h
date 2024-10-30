#pragma once

#include "GameState.h"
#include <unordered_map>
#include <string>
#include "GameObject.h"

class InputManager;
class Game;

class TitleScreenState :
    public GameState
{
public:
    TitleScreenState();
    ~TitleScreenState()override;

    void update(Game* game,InputManager* inputManager)override;//スタートボタンが押されたらPlayingStateに遷移

    const std::unordered_map<std::wstring, GameObject*>* getGameObjects()const override;
private:
    std::unordered_map<std::wstring, GameObject*> gameObjects;//GameObjectと名前のペア
};