#pragma once
#include "GameState.h"
#include "PlayingState.h"
#include "Game.h"

class TitleScreenState :
    public GameState
{
public:
    TitleScreenState() {}
    ~TitleScreenState() {}
    void update(Game* game)override;//スタートボタンが押されたらPlayingStateに遷移
};

