#include "InPitchingSubState.h"

#include "TitleScreenState.h"
#include "InputManager.h"
#include "Game.h"
#include "PlayingState.h"

using namespace std;

InPitchingSubState::InPitchingSubState(PlayingState& context):
    GameSubState(context)
{
    std::wstring message = L"InPitchingSubState�J�n\n";
    OutputDebugString(message.c_str());
}

void InPitchingSubState::update()
{
    //�s�b�`���O�A�j���[�V�����̍X�V
    updatePitchingMotion();
    
    //
    const InputManager& inputManager = context.getConstGame().getConstInputManager();

    //EXIT�{�^���N���b�N���̏���
    {
        const GameObject& exitButton = context.getGameObject(L"BUTTON_EXIT");
        if (inputManager.isClicked(exitButton)) {
            context.getGame().changeState(make_unique<TitleScreenState>(context.getGame()));
            return;
        }
    }

    //�ȉ��ABUTTON_EXIT�N���b�N����

    //�o�b�^�[�̈ʒu���}�E�X�ʒu�ɍ��킹�ĕύX
    context.getBatter().updateBatterPos(inputManager);

    //�X�C���O�̃A�j���[�V��������
    context.updateBatterAnimation(inputManager);

    int currentBatterFrame = context.getGameObject(L"PICTURE_BATTER").getCurrentFrameNumber();
    //�Ō�����
    {
        if (2 <= currentBatterFrame && currentBatterFrame <= 4) {
            //context.getBatter().updateBatBoundingBox(currentBatterFrame);
        }


        if (currentBatterFrame >= 5) {
            //�o�b�g����g�̏���
            context.getGameObject(L"BOX_BAT").hide();
        }

    }
}



void InPitchingSubState::updatePitchingMotion()
{
}
