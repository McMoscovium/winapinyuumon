#include "AfterMeetSubState.h"

#include "Game.h"
#include "InputManager.h"
#include "GameObject.h"
#include "TitleScreenState.h"
#include "WaitingPitchingSubState.h"
#include "Ball.h"
#include <numbers>
#include <cmath>
#include "BallFlyingSubState.h"

void AfterMeetSubState::update(Game& game)
{
    Window* window = game.getWindow();
    PictureObject& ballObject = gameObjectManager.getObject<PictureObject>("BALL");
    Ball& ball = owner.getBall();
    PictureObject& shadow = gameObjectManager.getObject<PictureObject>("BALLSHADOW");

    //ボールが画面外に出たらchangeSubState
    if (!ballObject.isIntersectsWithClientRect(window)) {
        translateBall(ball);
        owner.changeSubState(new BallFlyingSubState(owner));
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

    //バッター座標、見た目の更新
    owner.updateBatterPos(inputManager);
    owner.updateBatterAnimation(inputManager);
    
    //ボールと影の座標の更新
    updateBallPos(ballObject, ball, shadow);
}

void AfterMeetSubState::enter(Game& game)
{
}

void AfterMeetSubState::exit(Game& game)
{
}

void AfterMeetSubState::updateBallPos(GameObject& ballObject, Ball& ball, GameObject& shadow)
{
    //ballのメンバ変数を更新
    POINT currentBallPos = ball.getPosition();
    LONG movementX = -(LONG)round(std::sin(static_cast<double>(ball.getAngle()) * std::numbers::pi / 180) * ball.getVelocity());
    LONG movementY = -(LONG)round(std::cos(static_cast<double>(ball.getAngle()) * std::numbers::pi / 180) * ball.getVelocity());
    POINT nextBallPos = {
        currentBallPos.x + movementX,
        currentBallPos.y + movementY
    };
    ball.setPosition(nextBallPos);
    ball.setHeight(ball.getHeight() + ball.getHVelocity());
    //影の描画位置を更新
    shadow.setObjectPosition({
        ball.getX() - (LONG)std::round(ball.getRadius() * shadow.getSizeRate()),
        ball.getY()
        });
    //ボールの描画位置を更新
    ballObject.setObjectPosition({
        shadow.getPositionX(),
        shadow.getPositionY() - (LONG)ball.getHeight()
    });
}

void AfterMeetSubState::translateBall(Ball& ball)
{
    POINT currentPos = ball.getPosition();
    POINT nextPos = {
        currentPos.x + 390,
        currentPos.y + 114
    };
    ball.setPosition(nextPos);
}
