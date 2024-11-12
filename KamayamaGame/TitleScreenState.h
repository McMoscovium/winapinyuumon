#pragma once

#include "GameState.h"
#include <vector>
#include <string>

class InputManager;
class Game;

class TitleScreenState :
    public GameState<TitleScreenState,GameSubState<TitleScreenState>>
{
public:
    TitleScreenState(Game& game);
    //状態を更新
    //スタートボタンが押されたらPlayingStateに遷移
    void update(Game& game)override;
};