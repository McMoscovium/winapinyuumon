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
    if (frame == 34) {//�{�[���������[�X
        owner.getGameObject(L"PICTURE_BALL").setObjectPosition({ 529,162 });
        owner.getGameObject(L"PICTURE_BALL").appear();
        owner.getGameObject(L"PICTURE_SHADOW").appear();
    }
    return;
}

void InPitchingSubState::updateBall()
{
    Ball& ball = owner.getBall();
    //�{�[���̃Q�[�����ʒu�̍X�V
    const POINT formerPos = ball.getPosition();
    const POINT nextPos = {
        formerPos.x,
        formerPos.y + pitchingSpeed
    };
    ball.setPosition(nextPos);
    
    //�����ڂ̍X�V
    GameObject& ballObject = owner.getGameObject(L"PICTURE_BALL");
    GameObject& shadow = owner.getGameObject(L"PICTURE_SHADOW");
    if (nextPos.y > 720) {
        //��ʉ��ɊO�ꂽ
        ballObject.hide();
        shadow.hide();
    }
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
    int angle = (int)std::round((cursorPos.y - ballPos.y) * 9 / 5);
    ball.setAngle(angle);
    //����
    int speed = 50 - abs(ballPos.x - cursorPos.x);
    ball.setVelocity(speed);
    //������̑��x
    int hVelocity = 20;
    ball.sethVelocity(hVelocity);
    std::wstring message = L"angle: " + std::to_wstring(angle) + L"\n";
    std::wstring msg2 = L"speed: " + std::to_wstring(speed) + L"\n";
    OutputDebugString(message.c_str());
    OutputDebugStringW(msg2.c_str());
    //�Ō��true��Ԃ�
    return true;
}

void InPitchingSubState::update(Game& game)
{

    Ball& ball = owner.getBall();
    GameObject& ballObject = owner.getGameObject(L"PICTURE_BALL");
    GameObject& shadow = owner.getGameObject(L"PICTURE_SHADOW");
    GameObject& pitcher = owner.getGameObject(L"PICTURE_PITCHER");
    
    
    //�������{�[������ʉ��܂ōs������changeState
    if (ball.getY() > 700) {//��ʉ��ɊO�ꂽ
        
        ballObject.hide();
        shadow.hide();
        owner.changeSubState(new WaitingPitchingSubState(owner));
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

    //�{�[�����W�̍X�V
    if (ballObject.isVisible() == true) {
        updateBall();
    }

    //�{�[�������ڂ̍X�V
    int frame = pitcher.getCurrentFrameNumber();
    if (frame == 34) {//�{�[���������[�X
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
    

    //�s�b�`���O�A�j���[�V�����̍X�V
    if (frame < pitcher.getLength() - 1) {
        pitcher.nextFrame();
    }
    
    //�o�b�^�[�̍X�V
    owner.updateBatterPos(inputManager);
    owner.updateBatterAnimation(inputManager);

    //�Ō�����
    int currentBatterFrame = owner.getGameObject(L"PICTURE_BATTER").getCurrentFrameNumber();
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
        OutputDebugString(L"pitcher��nullptr�ł�\n");
    }
    OutputDebugString(L"Entering InPitchingState\n");
}

void InPitchingSubState::exit(Game& game)
{
    owner.getGameObject(L"JUDGE_BAT").hide();
    owner.getGameObject(L"PICTURE_PITCHER").changeFrame(0);//�s�b�`���[�t���[��������
    OutputDebugString(L"Exitting InPitchingState\n");
}
