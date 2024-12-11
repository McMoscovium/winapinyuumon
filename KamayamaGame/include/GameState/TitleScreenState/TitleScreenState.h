#pragma once

#include "GameState/GameState.h"

#include "GameObject/PictureObject.h"

class InputManager;
class Game;

class TitleScreenState :
    public GameState<TitleScreenState,GameSubState<TitleScreenState>>
{
private:
public:
    TitleScreenState(Game& game);
    //状態を更新
    //スタートボタンが押されたらPlayingStateに遷移
    void update(Game& game)override;
};