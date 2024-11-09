#include "WaitingPitchingSubState.h"

#include <memory>
#include "InPitchingSubState.h"
#include "InputManager.h"
#include "Game.h"
#include "TitleScreenState.h"


using namespace std;

WaitingPitchingSubState::WaitingPitchingSubState(PlayingState& context) :GameSubState<PlayingState>(context)
{
    std::wstring message = L"WaitingPitchingSubState�J�n\n";
    OutputDebugString(message.c_str());
    //�J�n�������L�^
    timer.recordTime();
}

void WaitingPitchingSubState::update()
{
    //�^�C�}�[�̍X�V
    timer.update();
    //�^�C�}�[�̃`�F�b�N
    if (timer.span() > 5000) {//�J�n����5000ms�o��
        //�t�F�[�Y��IN_PITCHING�ɕύX
        context.changeSubState(make_unique<InPitchingSubState>(context));
        return;
    }

    Game& game = context.getGame();
    const InputManager& inputManager = game.getConstInputManager();

    //�I���{�^���̏���
    GameObject& exitButton = context.getGameObject(L"BUTTON_EXIT");
    if (inputManager.isClicked(exitButton)) {
        game.changeState(make_unique<TitleScreenState>(game));
        return;
    }

    //�ȉ��ABUTTON_EXIT�N���b�N����

    //�o�b�^�[�̈ʒu���X�V
    context.getBatter().updateBatterPos(inputManager);

    //�X�C���O�̃A�j���[�V��������
    context.getBatter().updateSwingAnimation(inputManager);

    //�Ō�����
    int currentBatterFrame = context.getBatter().getCurrentFrameNumber();
    if (2 <= currentBatterFrame && currentBatterFrame <= 4) {
        //context.getBoundingBox().appear();
        //context.getBatter().updateBatBoundingBox(currentBatterFrame);
    }

    if (currentBatterFrame >= 5) {
            //�o�b�g����g�̏���
        context.getBoundingBox().hide();
    }
}

