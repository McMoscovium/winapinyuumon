#pragma once

#include"GameState.h"

#include <string>
#include <vector>

class Game;
class InputManager;
class Vector2D;

class PlayingState :
    public GameState
{
public:
    enum Phase {
        WAITING_PITCHING,
        IN_PITCHING,
        BALL_FLYING
    };

    

    PlayingState();

    //アップデート関数
    //ゲームが終了したらGameOverStateに遷移
    void update(Game* game,InputManager* inputManager)override;
    void updateWaitingPitchingPhase(InputManager* inputManager, Game* game);
    void updateBatFrame(int currentBatterFrame);
    void updateInPitchingPhase(InputManager* inputManager, Game* game);
    void updateCursorPos(InputManager* inputManager);
    //バッターのアニメーション更新
    void updateBatterAnimation(InputManager* inputManager);
    //バッターの位置更新
    void updateBatterPos(InputManager* inputManager);
    //
    const POINT getCursorPos()const;
    //フェイズ開始時の時刻を記録
    void initializeStartTime();

private://メンバ変数
    //animateBatter()に使う変数
    bool releasedLeftButtonUntilSwingEnded = false;
    //バッターの移動スピード
    int batterMovementSpeed = 10;
    //バッターが移動可能な範囲
    const RECT batterBox = { 178,266,355,357 };
    //ヒッティングカーソルの位置
    POINT cursorPos = { 0,0 };
    //フェーズ
    Phase phase = WAITING_PITCHING;
    //フェーズ開始時刻
    DWORD phaseStartTime = 0;
    //WAITING_PITCHING用タイマー
    DWORD waitingPitchingTimer = 0;
    //
    void updateWaitingPitchingTimer();
    //
    void changePhase(Phase phase);

    //スイング中のヒッティング判定
    void hitting();
    //
    POINT nextKamayamaPos(POINT position, Vector2D movement);
    //
    void updatePitchingMotion();
};