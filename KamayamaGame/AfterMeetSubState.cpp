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
    GameObject& ballObject = owner.getGameObject(L"PICTURE_BALL");
    Ball& ball = owner.getBall();
    GameObject& shadow = owner.getGameObject(L"PICTURE_SHADOW");

    //�{�[������ʊO�ɏo����changeSubState
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
    
    //�{�[���Ɖe�̍��W�̍X�V
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
    //ball�̃����o�ϐ����X�V
    POINT currentBallPos = ball.getPosition();
    LONG movementX = -round(std::sin(static_cast<double>(ball.getAngle()) * std::numbers::pi / 180) * ball.getVelocity());
    LONG movementY = -round(std::cos(static_cast<double>(ball.getAngle()) * std::numbers::pi / 180) * ball.getVelocity());
    POINT nextBallPos = {
        currentBallPos.x + movementX,
        currentBallPos.y + movementY
    };
    ball.setPosition(nextBallPos);
    ball.sethVelocity(ball.getHVelocity() - ball.getGravity());
    ball.setHeight(ball.getHeight() + ball.getHVelocity());
    //�e�̕`��ʒu���X�V
    shadow.setObjectPosition({
        ball.getX() - (LONG)std::round(ball.getRadius() * shadow.getSizeRate()),
        ball.getY()
        });
    //�{�[���̕`��ʒu���X�V
    ballObject.setObjectPosition({
        shadow.getPositionX(),
        shadow.getPositionY() - ball.getHeight()
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
