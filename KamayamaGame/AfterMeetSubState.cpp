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
    //�{�[������ʊO�ɏo����changeSubState
    Window* window = game.getWindow();
    GameObject& ballObject = owner.getGameObject(L"PICTURE_BALL");
    Ball& ball = owner.getBall();
    if (ballObject.isOutOfClientRect(window)) {
        translateBall(ball);
        owner.changeSubState(new BallFlyingSubState(owner));
        return;
    }

    //�I���{�^������
    InputManager& inputManager = game.getInputManager();
    GameObject& exitButton = owner.getGameObject(L"BUTTON_EXIT");
    if (inputManager.isClicked(exitButton)) {
        exit(game);//�I������
        game.changeState(new TitleScreenState(game));
        return;
    }

    //�o�b�^�[���W�A�����ڂ̍X�V
    owner.updateBatterPos(inputManager);
    owner.updateBatterAnimation(inputManager);
    
    //�{�[�����W�̍X�V
    updateBallPos(ballObject, ball);
}

void AfterMeetSubState::enter(Game& game)
{
}

void AfterMeetSubState::exit(Game& game)
{
}

void AfterMeetSubState::updateBallPos(GameObject& ballObject, Ball& ball)
{
    POINT currentBallPos = ballObject.getPosition();
    LONG movementX = -round(std::sin(static_cast<double>(ball.getAngle()) * std::numbers::pi / 180) * ball.getVelocity());
    LONG movementY = -round(std::cos(static_cast<double>(ball.getAngle()) * std::numbers::pi / 180) * ball.getVelocity());
    POINT nextPos = {
        currentBallPos.x + movementX,
        currentBallPos.y + movementY
    };
    ballObject.setObjectPosition(nextPos);
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
