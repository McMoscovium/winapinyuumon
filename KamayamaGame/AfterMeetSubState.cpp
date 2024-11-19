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

    //�{�[������ʊO�ɏo����changeSubState
    if (!ballObject.isIntersectsWithClientRect(window)) {
        translateBall(ball);
        owner.changeSubState(new BallFlyingSubState(owner));
        return;
    }

    //�I���{�^������
    InputManager& inputManager = game.getInputManager();
    PictureObject& exitButton = gameObjectManager.getObject<PictureObject>("EXIT");
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
    LONG movementX = -(LONG)round(std::sin(static_cast<double>(ball.getAngle()) * std::numbers::pi / 180) * ball.getVelocity());
    LONG movementY = -(LONG)round(std::cos(static_cast<double>(ball.getAngle()) * std::numbers::pi / 180) * ball.getVelocity());
    POINT nextBallPos = {
        currentBallPos.x + movementX,
        currentBallPos.y + movementY
    };
    ball.setPosition(nextBallPos);
    ball.setHeight(ball.getHeight() + ball.getHVelocity());
    //�e�̕`��ʒu���X�V
    shadow.setObjectPosition({
        ball.getX() - (LONG)std::round(ball.getRadius() * shadow.getSizeRate()),
        ball.getY()
        });
    //�{�[���̕`��ʒu���X�V
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
