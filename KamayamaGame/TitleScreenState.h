#pragma once

#include "GameState.h"
#include <vector>
#include <string>

class InputManager;
class Game;

class TitleScreenState :
    public GameState
{
public:
    //メンバ変数

private:
    //メンバ変数

public:
    //メンバ関数

    TitleScreenState();

    //状態を更新
    //スタートボタンが押されたらPlayingStateに遷移
    void update(Game* game, InputManager* inputManager)override;

private:
    //メンバ関数
};