#pragma once

#include"GameState.h"

#include <string>
#include <vector>

class Game;
class InputManager;

class PlayingState :
    public GameState
{
public:
    PlayingState();

    //アップデート関数
    //ゲームが終了したらGameOverStateに遷移
    void update(Game* game,InputManager* inputManager)override;
    //バッターのアニメーション更新
    void animateBatter(InputManager* inputManager);
    //バッターの位置更新
    void updateBatterPos(InputManager* inputManager);
private://メンバ変数
    //animateBatter()に使う変数
    bool releasedLeftButtonUntilSwingEnded = false;
    //バッターの移動スピード
    int batterMovementSpeed = 1;
    //バッターが移動可能な範囲
    const RECT batterBox = { 172,262,255,375 };
};