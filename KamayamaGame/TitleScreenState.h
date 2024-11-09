#pragma once

#include "GameState.h"
#include <vector>
#include <string>
#include <memory>

class InputManager;
class Game;

class TitleScreenState :
    public GameState<TitleScreenState>
{
public:
    using SubStateType = GameSubState<TitleScreenState>;
    
    TitleScreenState(Game& game);

    //状態を更新
    //スタートボタンが押されたらPlayingStateに遷移
    void update()override;

private:
    //メンバ関数
};