#pragma once

#include"GameState.h"

#include <string>
#include <vector>
#include "Ball.h"
#include "Vector2D.h"
#include <unordered_map>

class pitcher;
class Batter;
class Game;
class InputManager;

class PlayingState :
    public GameState<PlayingState,GameSubState<PlayingState>>
{
public:
    PlayingState(Game& game, Batter* batter, Pitcher* pitcher);
    ~PlayingState();

    //アップデート関数
    //ゲームが終了したらGameOverStateに遷移
    void update(Game& game)override;
    void updateBatFrame(int currentBatterFrame);
    //バッターのアニメーション更新
    void updateBatterAnimation(const InputManager& inputManager);
    //バッターの位置更新
    void updateBatterPos(const InputManager& inputManager);
    //
    const POINT getCursorPos()const;
    //フェイズ開始時の時刻を記録
    void initializeStartTime();
    //
    Ball& getBall();
    //
    Pitcher* getPitcher();
    //
    int& getDistance();
    //
    std::unordered_map<std::wstring, GameObject&>& getFieldImages();
    //バッターの位置をposにする。posがバッターボックスからはみ出ていたらボックスにいれる。
    void setBatterInBox(POINT pos);


private:
    Ball ball;
    Pitcher* pitcher;
    Batter* batter;
    //animateBatter()に使う変数
    bool releasedLeftButtonUntilSwingEnded = false;
    //バッターの移動スピード
    int batterMovementSpeed = 4;
    //バッターが移動可能な範囲
    const RECT batterBox = { 178,266,355,357 };
    //ヒッティングカーソルの位置
    POINT cursorPos = { 0,0 };
    //フェーズ開始時刻
    ULONGLONG phaseStartTime = 0;
    //WAITING_PITCHING用タイマー
    ULONGLONG waitingPitchingTimer = 0;
    //飛距離を記録する変数
    int distance = 0;
    //フィールド画像への参照の列
    std::unordered_map<std::wstring, GameObject&> fieldImages;



    //
    void updateWaitingPitchingTimer();

    //スイング中のヒッティング判定
    void hitting();
    //
    POINT nextKamayamaPos(POINT position, Vector2D<float> movement);
    //
    void updatePitchingMotion();
};