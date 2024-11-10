#include "InPitchingSubState.h"

#include "Game.h"
#include "InputManager.h"
#include "GameObject.h"
#include "TitleScreenState.h"
#include "WaitingPitchingSubState.h"

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

void InPitchingSubState::update(Game& game)
{
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
    //�{�[���̍X�V
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
    owner.getGameObject(L"PICTURE_PITCHER").changeFrame(0);//�s�b�`���[�t���[��������
    OutputDebugString(L"Exitting InPitchingState\n");
}
