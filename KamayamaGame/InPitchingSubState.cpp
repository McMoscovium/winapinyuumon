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
    }
    return;
}

void InPitchingSubState::updateBall()
{
    GameObject& ball = owner.getGameObject(L"PICTURE_BALL");
    //位置の更新
    const POINT formerPos = ball.getPosition();
    const POINT nextPos = {
        formerPos.x,
        formerPos.y + pitchingSpeed
    };
    ball.setObjectPosition(nextPos);

    //見た目の更新
    if (nextPos.y > 720) {
        ball.hide();
    }
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
    int angle = std::round((cursorPos.y - ballPos.y) * 9 / 5);
    ball.setAngle(angle);
    int speed = 50 - abs(ballPos.x - cursorPos.x);
    ball.setVelocity(speed);
    std::wstring message = L"angle: " + std::to_wstring(angle) + L"\n";
    std::wstring msg2 = L"speed: " + std::to_wstring(speed) + L"\n";
    OutputDebugString(message.c_str());
    OutputDebugStringW(msg2.c_str());
    //最後にtrueを返す
    return true;
}

void InPitchingSubState::update(Game& game)
{
    //投げたボールが画面下まで行ったらchangeState
    GameObject& ball = owner.getGameObject(L"PICTURE_BALL");
    if (ball.getPositionY() > 700) {//画面下に外れた
        ball.hide();
        owner.changeSubState(new WaitingPitchingSubState(owner));
        return;
    }

    InputManager& inputManager = game.getInputManager();
	//終了ボタン処理
    GameObject& exitButton = owner.getGameObject(L"BUTTON_EXIT");
    if (inputManager.isClicked(exitButton)) {
        exit(game);//終了処理
        game.changeState(new TitleScreenState(game));
        return;
    }

    //ピッチングアニメーションの更新
    updatePitchingMotion();
    //ボール座標の更新
    if (owner.getGameObject(L"PICTURE_BALL").isVisible() == true) {
        updateBall();
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
        if (calculateMeet(ball, owner.getBall())) {
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
    
    owner.getGameObject(L"PICTURE_BALL").setObjectPosition({ 529,162 });//ボール座標初期化
    OutputDebugString(L"Entering InPitchingState\n");
}

void InPitchingSubState::exit(Game& game)
{
    owner.getGameObject(L"JUDGE_BAT").hide();
    owner.getGameObject(L"PICTURE_PITCHER").changeFrame(0);//ピッチャーフレーム初期化
    OutputDebugString(L"Exitting InPitchingState\n");
}
