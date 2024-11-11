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
    if (frame == 34) {//�{�[���������[�X
        owner.getGameObject(L"PICTURE_BALL").setObjectPosition({ 529,162 });
        owner.getGameObject(L"PICTURE_BALL").appear();
    }
    return;
}

void InPitchingSubState::updateBall()
{
    GameObject& ball = owner.getGameObject(L"PICTURE_BALL");
    //�ʒu�̍X�V
    const POINT formerPos = ball.getPosition();
    const POINT nextPos = {
        formerPos.x,
        formerPos.y + pitchingSpeed
    };
    ball.setObjectPosition(nextPos);

    //�����ڂ̍X�V
    if (nextPos.y > 720) {
        ball.hide();
    }
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
    int angle = std::round((cursorPos.y - ballPos.y) * 9 / 5);
    ball.setAngle(angle);
    int speed = 50 - abs(ballPos.x - cursorPos.x);
    ball.setVelocity(speed);
    std::wstring message = L"angle: " + std::to_wstring(angle) + L"\n";
    std::wstring msg2 = L"speed: " + std::to_wstring(speed) + L"\n";
    OutputDebugString(message.c_str());
    OutputDebugStringW(msg2.c_str());
    //�Ō��true��Ԃ�
    return true;
}

void InPitchingSubState::update(Game& game)
{
    //�������{�[������ʉ��܂ōs������changeState
    GameObject& ball = owner.getGameObject(L"PICTURE_BALL");
    if (ball.getPositionY() > 700) {//��ʉ��ɊO�ꂽ
        ball.hide();
        owner.changeSubState(new WaitingPitchingSubState(owner));
        return;
    }

    InputManager& inputManager = game.getInputManager();
	//�I���{�^������
    GameObject& exitButton = owner.getGameObject(L"BUTTON_EXIT");
    if (inputManager.isClicked(exitButton)) {
        exit(game);//�I������
        game.changeState(new TitleScreenState(game));
        return;
    }

    //�s�b�`���O�A�j���[�V�����̍X�V
    updatePitchingMotion();
    //�{�[�����W�̍X�V
    if (owner.getGameObject(L"PICTURE_BALL").isVisible() == true) {
        updateBall();
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
        if (calculateMeet(ball, owner.getBall())) {
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
    
    owner.getGameObject(L"PICTURE_BALL").setObjectPosition({ 529,162 });//�{�[�����W������
    OutputDebugString(L"Entering InPitchingState\n");
}

void InPitchingSubState::exit(Game& game)
{
    owner.getGameObject(L"JUDGE_BAT").hide();
    owner.getGameObject(L"PICTURE_PITCHER").changeFrame(0);//�s�b�`���[�t���[��������
    OutputDebugString(L"Exitting InPitchingState\n");
}
