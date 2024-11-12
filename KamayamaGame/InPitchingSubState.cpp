#include "InPitchingSubState.h"

#include "Game.h"
#include "InputManager.h"
#include "GameObject.h"
#include "TitleScreenState.h"
#include "WaitingPitchingSubState.h"
#include "AfterMeetSubState.h"
#include "Vector2D.h"
#include <cmath>
#include "Ball.h"
#include <Windows.h>

void InPitchingSubState::updatePitchingMotion()
{
    GameObject& pitcher = owner.getGameObject(L"PICTURE_PITCHER");
    int frame = pitcher.getCurrentFrameNumber();
    if (frame < pitcher.getLength() - 1) {
        pitcher.nextFrame();
    }
    if (frame == 34) {//ボールをリリース
        owner.getGameObject(L"PICTURE_BALL").setObjectPosition({ 529,162 });
        owner.getGameObject(L"PICTURE_BALL").appear();
        owner.getGameObject(L"PICTURE_SHADOW").appear();
    }
    return;
}

void InPitchingSubState::updateBall()
{
    Ball& ball = owner.getBall();
    //ボールのゲーム内位置の更新
    const POINT formerPos = ball.getPosition();
    const POINT nextPos = {
        formerPos.x,
        formerPos.y + pitchingSpeed
    };
    ball.setPosition(nextPos);
    
    //見た目の更新
    GameObject& ballObject = owner.getGameObject(L"PICTURE_BALL");
    GameObject& shadow = owner.getGameObject(L"PICTURE_SHADOW");
    if (nextPos.y > 720) {
        //画面下に外れた
        ballObject.hide();
        shadow.hide();
    }
    //以下、画面下に外れてない
    // //ボールと影のサイズを更新
    ballObject.changeSizeRate(
        (float)(1440 - (720 - ball.getY())) / (float)1440
    );
    shadow.changeSizeRate(
        (float)(1440 - (720 - ball.getY())) / (float)1440
    );
    //影とボールの位置を更新
    POINT shadowPos = {
        nextPos.x - (LONG)(17*shadow.getSizeRate()),
        nextPos.y
    };
    shadow.setObjectPosition(shadowPos);
    POINT objectPos = {
        //ボールの半径だけxざひょうをずらす
        nextPos.x-(LONG)std::round(
            ball.getRadius()*ballObject.getSizeRate()
        ),
        nextPos.y - (int)std::round(ball.getHeight()*ballObject.getSizeRate())
    };
    ballObject.setObjectPosition(objectPos);
    
    
}

bool InPitchingSubState::calculateMeet(GameObject& ballObject, Ball& ball)
{
    POINT cursorPos = owner.getCursorPos();
    POINT ballPos = ballObject.getPosition();
    if (abs(ballPos.y - cursorPos.y) > 50) {
        //カーソルとボールのY座標が遠い
        return false;
    }
    if (abs(ballPos.x - cursorPos.x) > 50) {
        //カーソルとボールのX座標が遠い
        return false;
    }
    //以下、ボールとバットが当たった
    //ボールの速度データを計算
    //左右の角度
    int angle = (int)std::round((cursorPos.y - ballPos.y) * 9 / 5);
    ball.setAngle(angle);
    //早さ
    int speed = 50 - abs(ballPos.x - cursorPos.x);
    ball.setVelocity(speed);
    //上向きの速度
    int hVelocity = 20;
    ball.sethVelocity(hVelocity);
    std::wstring message = L"angle: " + std::to_wstring(angle) + L"\n";
    std::wstring msg2 = L"speed: " + std::to_wstring(speed) + L"\n";
    OutputDebugString(message.c_str());
    OutputDebugStringW(msg2.c_str());
    //最後にtrueを返す
    return true;
}

void InPitchingSubState::update(Game& game)
{

    Ball& ball = owner.getBall();
    GameObject& ballObject = owner.getGameObject(L"PICTURE_BALL");
    GameObject& shadow = owner.getGameObject(L"PICTURE_SHADOW");
    GameObject& pitcher = owner.getGameObject(L"PICTURE_PITCHER");
    
    
    //投げたボールが画面下まで行ったらchangeState
    if (ball.getY() > 700) {//画面下に外れた
        
        ballObject.hide();
        shadow.hide();
        owner.changeSubState(new WaitingPitchingSubState(owner));
        return;
    }

    //終了ボタン処理
    InputManager& inputManager = game.getInputManager();
    GameObject& exitButton = owner.getGameObject(L"BUTTON_EXIT");
    if (inputManager.isClicked(exitButton)) {
        exit(game);//終了処理
        game.changeState(new TitleScreenState(game));
        return;
    }

    //ボール座標の更新
    if (ballObject.isVisible() == true) {
        updateBall();
    }

    //ボール見た目の更新
    int frame = pitcher.getCurrentFrameNumber();
    if (frame == 34) {//ボールをリリース
        ballObject.setObjectPosition({
            ball.getX(),
            ball.getY() + (LONG)ball.getHeight()
            });
        ballObject.changeSizeRate(
            (float)(1440 - (720 - ball.getY())) / (float)1440
        );
        ballObject.appear();
        shadow.setObjectPosition(ball.getPosition());
        shadow.appear();
    }
    

    //ピッチングアニメーションの更新
    if (frame < pitcher.getLength() - 1) {
        pitcher.nextFrame();
    }
    
    //バッターの更新
    owner.updateBatterPos(inputManager);
    owner.updateBatterAnimation(inputManager);

    //打撃処理
    int currentBatterFrame = owner.getGameObject(L"PICTURE_BATTER").getCurrentFrameNumber();
    if (2 <= currentBatterFrame && currentBatterFrame <= 4) {
        //当たり判定が登場
        owner.updateBatFrame(currentBatterFrame);
        //ボールが当たったかどうかで分けて処理
        if (calculateMeet(ballObject, owner.getBall())) {
            owner.changeSubState(new AfterMeetSubState(owner));
            return;
        }
        return;
    }

    if (currentBatterFrame >= 5) {
        //バット判定枠の消去
        owner.getGameObject(L"JUDGE_BAT").hide();
    }
}

void InPitchingSubState::enter(Game& game)
{
    Ball& ball = owner.getBall();
    ball.setPosition({ 542,115 });
    Pitcher* pitcher = owner.getPitcher();
    if (pitcher) {
        pitcher->decideNextPitch();
    }
    else {
        OutputDebugString(L"pitcherはnullptrです\n");
    }
    OutputDebugString(L"Entering InPitchingState\n");
}

void InPitchingSubState::exit(Game& game)
{
    owner.getGameObject(L"JUDGE_BAT").hide();
    owner.getGameObject(L"PICTURE_PITCHER").changeFrame(0);//ピッチャーフレーム初期化
    OutputDebugString(L"Exitting InPitchingState\n");
}
