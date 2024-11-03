#pragma once

#include"GameState.h"

#include <string>
#include <vector>

class Game;
class InputManager;

class PlayingState :
    public GameState
{
public://メンバ変数
private://メンバ変数
    bool releasedLeftButtonUntilSwingEnded = false;

public://メンバ関数
    PlayingState();
    //アップデート関数
    //ゲームが終了したらGameOverStateに遷移
    void update(Game* game,InputManager* inputManager)override;

private:
};