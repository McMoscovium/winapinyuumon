#include "CompareNormSubState.h"

#include "Game.h"
#include "InputManager.h"

void CompareNormSubState::update(Game& game)
{
	timer.update();
	//1500ms���܂ł܂�
	if (timer.span() < 1500) {
		return;
	}

	//�ȉ��A1500ms������

	//�N���A�A�j���[�V������\�����I����
	if (clearPictureFrame == 20) {
		owner.getGameObject(L"BUTTON_NEXT").appear();
	}

	//�A�j���[�V�����X�V
	if (clearPictureFrame < 20) {
		GameObject& clearPicture = owner.getGameObject(clearPictureName);
		clearPicture.setObjectPosition({
			448 - (20 - clearPictureFrame) * 50,
			590
			});
		clearPicture.appear();
		clearPictureFrame++;
	}

	//���փ{�^������
	GameObject& nextButton = owner.getGameObject(L"BUTTON_NEXT");
	InputManager& inputManager = game.getInputManager();
	if (inputManager.isClicked(nextButton)) {
		//���փ{�^���������ꂽ
		OutputDebugString(L"���փ{�^���������ꂽ\n");
	}


}

void CompareNormSubState::enter(Game& game)
{
	owner.getGameObject(L"PICTURE_KEKKAHAPPYOU").appear();
	owner.getGameObject(L"TEXT_BALLS").appear();
	owner.getGameObject(L"TEXT_NORM").appear();
	owner.getGameObject(L"TEXT_RUNS").appear();
	owner.getGameObject(L"TEXT_PITCHERNAME").appear();
}

void CompareNormSubState::exit(Game& game)
{
}
