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
    Pitcher* pitcher = owner.getPitcher();
    Ball& ball = owner.getBall();
    
    POINT nextPos = ball.updatePitch(pitcher);

    //�����ڂ̍X�V
    GameObject& ballObject = gameObjectManager.getObject<PictureObject>("BALL");
    GameObject& shadow = gameObjectManager.getObject<PictureObject>("BALLSHADOW");
    //�ȉ��A��ʉ��ɊO��ĂȂ�
    // //�{�[���Ɖe�̃T�C�Y���X�V
    ballObject.changeSizeRate(
        (float)(1440 - (720 - ball.getY())) / (float)1440
    );
    shadow.changeSizeRate(
        (float)(1440 - (720 - ball.getY())) / (float)1440
    );
    //�e�ƃ{�[���̈ʒu���X�V
    POINT shadowPos = {
        nextPos.x - (LONG)(17*shadow.getSizeRate()),
        nextPos.y
    };
    shadow.setObjectPosition(shadowPos);
    POINT objectPos = {
        //�{�[���̔��a����x���Ђ傤�����炷
        nextPos.x - (LONG)std::round(
            ball.getRadius() * ballObject.getSizeRate()
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
        //�J�[�\���ƃ{�[����Y���W������
        return false;
    }
    if (abs(ballPos.x - cursorPos.x) > 50) {
        //�J�[�\���ƃ{�[����X���W������
        return false;
    }
    //�ȉ��A�{�[���ƃo�b�g����������
    
    //�{�[���̑��x�f�[�^���v�Z
    
    //���E�̊p�x
    float angle = (float)std::round((cursorPos.y - ballPos.y) * 1.8f);
    ball.setAngle(angle);

    //efficiency�̌v�Z
    float efficiency = 0;//1�ɋ߂��قǃW���X�g�~�[�g
    efficiency = (50 - abs(ballPos.x + ball.getRadius() * ballObject.getSizeRate() - cursorPos.x)) / 40;

    //������̑�����ݒ�
    Batter* batter = owner.getBatter();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> dis(0.6f,0.1f);
    float hVelocity = (
        batter->getPower() * efficiency +
        (1 - efficiency) * ball.getVelocity()
        ) * std::max<float>(dis(gen), 0.1f);
    ball.sethVelocity(hVelocity);

    //�����̐�������    
    int speed = (int)(batter->getPower() * efficiency);
    ball.setVelocity(speed);
    
    //�Ō��true��Ԃ�
    return true;
}

void InPitchingSubState::update(Game& game)
{
    Ball& ball = owner.getBall();
    PictureObject& ballObject = gameObjectManager.getObject<PictureObject>("BALL");
    GameObject& shadow = gameObjectManager.getObject<PictureObject>("BALLSHADOW");
    PictureObject& pitcher = gameObjectManager.getObject<PictureObject>("PITCHER");
    
    
    //�������{�[������ʉ��܂ōs������changeState
    if (ball.getY() > 700) {//��ʉ��ɊO�ꂽ
        
        ballObject.hide();
        shadow.hide();
        owner.changeSubState(new BattingResultSubState(owner, PlayingState::FlyBallResult::STRIKE));
        
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

    //�{�[�����W�̍X�V
    if (ballObject.isVisible() == true) {
        updateBall();
    }

    //�{�[�������ڂ̍X�V
    int frame = pitcher.getCurrentFrameNumber();
    if (frame == 34) {//�{�[���������[�X
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
    

    //�s�b�`���O�A�j���[�V�����̍X�V
    if (frame < pitcher.getLength() - 1) {
        pitcher.nextFrame();
    }
    
    //�o�b�^�[�̍X�V
    owner.updateBatterPos(inputManager);
    owner.updateBatterAnimation(inputManager);

    //�Ō�����
    int currentBatterFrame = gameObjectManager.getObject<PictureObject>("BATTER").getCurrentFrameNumber();
    if (2 <= currentBatterFrame && currentBatterFrame <= 4) {
        //�����蔻�肪�o��
        owner.updateBatFrame(currentBatterFrame);
        //�{�[���������������ǂ����ŕ����ď���
        if (calculateMeet(ballObject, owner.getBall())) {
            owner.changeSubState(new AfterMeetSubState(owner));
            return;
        }
        return;
    }

    if (currentBatterFrame >= 5) {
        //�o�b�g����g�̏���
        gameObjectManager.getObject<PictureObject>("BAT_HITBOX").hide();
    }
}

void InPitchingSubState::enter(Game& game)
{
    //�{�[���̏����ʒu
    Ball& ball = owner.getBall();
    ball.setHeight(70);
    ball.setPosition({ 542,115 });
    ball.sethVelocity(0);
    ball.setVelocity(0);

    //���̋��������
    Pitcher* pitcher = owner.getPitcher();
    pitcher->decideNextPitch();

    //���肵������ɏ]���{�[���̏������x��ݒ�
    
    ball.setVelocity(pitcher->getPitchingSpeed());
    ball.setAngle(pitcher->getPitchingAngle() + 180.0f);

    //�c�苅�������炷
    owner.getRestBalls()--;
    
    OutputDebugString(L"Entering InPitchingState\n");
}

void InPitchingSubState::exit(Game& game)
{
    gameObjectManager.getObject<PictureObject>("BAT_HITBOX").hide();
    gameObjectManager.getObject<PictureObject>("PITCHER").changeFrame(0);//�s�b�`���[�t���[��������
    OutputDebugString(L"Exitting InPitchingState\n");
}