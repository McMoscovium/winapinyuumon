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
#include "Batter.h"
#include "EndPlayingSubState.h"
#include "BattingResultSubState.h"
#include <random>
#include "PictureObject.h"
#include "Pitcher.h"
#include "CutIn.h"

#include <typeinfo>

void InPitchingSubState::updatePitchingMotion()
{
    PictureObject& pitcher = gameObjectManager.getObject<PictureObject>("PITCHER");
    int frame = pitcher.getCurrentFrameNumber();
    if (frame < pitcher.getLength() - 1) {
        pitcher.nextFrame();
    }
    return;
}

void InPitchingSubState::updateBall()
{
    Pitcher& pitcher = owner.getGameObjectManager().getObject<Pitcher>("PITCHER");
    Ball& ball = owner.getBall();
    
    POINT nextPos = ball.updatePitch(&pitcher);

    //見た目の更新
    GameObject& ballObject = gameObjectManager.getObject<PictureObject>("BALL");
    GameObject& shadow = gameObjectManager.getObject<PictureObject>("BALLSHADOW");
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
        nextPos.x - (LONG)std::round(
            ball.getRadius() * ballObject.getSizeRate()
        ),
        nextPos.y - (int)std::round(ball.getHeight()*ballObject.getSizeRate())
    };
    ballObject.setObjectPosition(objectPos);   
}

bool InPitchingSubState::isMeet(GameObject& ballObject, Ball& ball, int& hitStopTime)
{
    POINT cursorPos = owner.getCursorPos();
    POINT ballPos = ballObject.getPosition();
    if (abs(ballPos.y - cursorPos.y) > 50) {
        //カーソルとボールのY座標が遠い
        return false;
    }
    if (abs(ballPos.x+ball.getRadius() - cursorPos.x) > 50) {
        //カーソルとボールのX座標が遠い
        return false;
    }
    //以下、ボールとバットが当たった
    
    int gap = abs(ballPos.x+ball.getRadius() - cursorPos.x);//ボールとカーソルのずれ具合
    std::wstring gapmsg = L"gap: " + std::to_wstring(gap) + L"\n";
    OutputDebugString(gapmsg.c_str());
    hitStopTime = 150 - 30 * gap;
    if (hitStopTime < 50) { hitStopTime = 0; }
    std::wstring msg = L"hitStopTime: "+std::to_wstring(hitStopTime) + L"\n";
    OutputDebugString(msg.c_str());

    //ボールの速度データを計算
    
    //左右の角度
    float angle = (float)std::round((cursorPos.y - ballPos.y) * 1.8f);
    ball.setAngle(angle);

    //efficiencyの計算
    float efficiency = 0;//1に近いほどジャストミート
    efficiency = (50 - abs(ballPos.x + ball.getRadius() * ballObject.getSizeRate() - cursorPos.x)) / 40;

    //上向きの早さを設定
    Batter& batter = owner.getGameObjectManager().getObject<Batter>("BATTER");
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> dis(0.6f,0.1f);
    float hVelocity = (
        batter.getPower() * efficiency +
        (1 - efficiency) * ball.getVelocity()
        ) * std::max<float>(dis(gen), 0.1f);
    ball.sethVelocity(hVelocity);

    //速さの水平成分    
    int speed = (int)(batter.getPower() * efficiency);
    if (hitStopTime > 0) {
        speed += 5;
    }
    ball.setVelocity(speed);
    

    //最後にtrueを返す
    return true;
}

void InPitchingSubState::update(Game& game)
{
    Ball& ball = owner.getBall();
    PictureObject& ballObject = gameObjectManager.getObject<PictureObject>("BALL");
    GameObject& shadow = gameObjectManager.getObject<PictureObject>("BALLSHADOW");
    Pitcher& pitcherObject = gameObjectManager.getObject<Pitcher>("PITCHER");
    
    
    //投げたボールが画面下まで行ったらchangeState
    if (ball.getY() > 700) {//画面下に外れた
        
        ballObject.hide();
        shadow.hide();
        owner.changeSubState(new BattingResultSubState(owner, PlayingState::FlyBallResult::STRIKE));
        
        return;
    }

    //終了ボタン処理
    InputManager& inputManager = game.getInputManager();
    PictureObject& exitButton = gameObjectManager.getObject<PictureObject>("EXIT");
    if (inputManager.isClicked(exitButton)) {
        exit(game);//終了処理
        game.changeState(new TitleScreenState(game));
        return;
    }

    //ボール座標の更新
    if (ballObject.isVisible() == true) {
        updateBall();
    }

    Pitcher& pitcher = owner.getGameObjectManager().getObject<Pitcher>("PITCHER");
    //ボール見た目の更新
    int frame = pitcherObject.getCurrentFrameNumber();
    if (frame == pitcher.releaseFrame) {//ボールをリリース
        POINT ballPos = ball.getPosition();
        ball.resetFrame();
        float sizeRate = (float)(1440 - (720 - ball.getY())) / (float)1440;
        ballObject.changeSizeRate(sizeRate);
        shadow.changeSizeRate(sizeRate);
        ballObject.setObjectPosition({
            ballPos.x - (LONG)std::round(sizeRate * ball.getRadius()),
            ballPos.y - (LONG)std::round(ball.getHeight() * sizeRate)
            });
        ballObject.appear();
        shadow.setObjectPosition({
            ballPos.x - (LONG)std::round(sizeRate * 17),
            ballPos.y
            });
        shadow.appear();
    }
    

    //ピッチングアニメーションの更新
    if (frame < pitcherObject.getLength() - 1) {
        pitcherObject.nextFrame();
    }
    
    //バッターの更新
    owner.updateBatterPos(inputManager);
    owner.updateBatterAnimation(inputManager);

    //打撃処理
    int currentBatterFrame = gameObjectManager.getObject<PictureObject>("BATTER").getCurrentFrameNumber();
    if (2 <= currentBatterFrame && currentBatterFrame <= 4) {
        //当たり判定が登場
        owner.updateBatFrame(currentBatterFrame);
        //ボールが当たったかどうかで分けて処理
        int hitStopTime = 0;
        if (isMeet(ballObject, owner.getBall(), hitStopTime)) {
            if (hitStopTime) {
                //ミート音を鳴らす
                owner.getAudioManager().play("JUST");
                //ジャストミート
                owner.changeSubState(new CutIn(owner, hitStopTime));
                return;
            }
            //じゃすとみーとじゃない
            owner.changeSubState(new AfterMeetSubState(owner, hitStopTime));
            return;
        }
        return;
    }

    if (currentBatterFrame >= 5) {
        //バット判定枠の消去
        gameObjectManager.getObject<PictureObject>("BAT_HITBOX").hide();
    }
}

void InPitchingSubState::enter(Game& game)
{
    //ボールの初期位置
    Ball& ball = owner.getBall();
    ball.setHeight(70);
    ball.setPosition({ 542,115 });
    ball.sethVelocity(0);
    ball.setVelocity(0);

    //次の球種を決定
    Pitcher& pitcher = owner.getGameObjectManager().getObject<Pitcher>("PITCHER");
    pitcher.decideNextPitch();

    //決定した球種に従いボールの初期速度を設定
    
    ball.setVelocity(pitcher.getPitchingSpeed());
    ball.setAngle(pitcher.getPitchingAngle() + 180.0f);

    //残り球数を減らす
    owner.getRestBalls()--;
    
    OutputDebugString(L"Entering InPitchingState\n");
}

void InPitchingSubState::exit(Game& game)
{
    gameObjectManager.getObject<PictureObject>("BAT_HITBOX").hide();
    gameObjectManager.getObject<PictureObject>("PITCHER").changeFrame(0);//ピッチャーフレーム初期化
    OutputDebugString(L"Exitting InPitchingState\n");
}
