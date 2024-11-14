#pragma once

#include"GameState.h"

#include <string>
#include <vector>
#include "Ball.h"
#include "Vector2D.h"
#include <unordered_map>
#include "Result.h"

class pitcher;
class Batter;
class Game;
class InputManager;
class Stadium;

class PlayingState :
    public GameState<PlayingState,GameSubState<PlayingState>>
{
public:
    PlayingState(Game& game, Batter* batter, Pitcher* pitcher, Stadium* stadium, int trials);
    ~PlayingState();

    enum FlyBallResult {
        HOMERUN,
        FOUL,
        HIT,
        STRIKE
    };


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
    int& getRestBalls();
    //
    Ball& getBall();
    //
    Batter* getBatter();
    //
    Pitcher* getPitcher();
    //
    Stadium* getStadium();
    int& getDistance();
    //
    std::unordered_map<std::wstring, GameObject&>& getFieldImages();
    //
    Result& getResult();
    //バッターの位置をposにする。posがバッターボックスからはみ出ていたらボックスにいれる。
    void setBatterInBox(POINT pos);


private:
    Ball ball;
    Pitcher* pitcher;
    Batter* batter;
    Stadium* stadium;
    //残り球数
    int restBalls;
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
    Result result;


    //
    void updateWaitingPitchingTimer();

    //スイング中のヒッティング判定
    void hitting();
    //
    POINT nextKamayamaPos(POINT position, Vector2D<float> movement);
    //
    void updatePitchingMotion();
};