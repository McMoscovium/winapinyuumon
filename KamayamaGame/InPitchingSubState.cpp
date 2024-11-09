#include "InPitchingSubState.h"

#include "Game.h"
#include "InputManager.h"
#include "GameObject.h"
#include "TitleScreenState.h"

void InPitchingSubState::updatePitchingMotion()
{
}

void InPitchingSubState::update(Game& game)
{
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
    OutputDebugString(L"Entering InPitchingState\n");
}

void InPitchingSubState::exit(Game& game)
{
    OutputDebugString(L"Exitting InPitchingState\n");
}
