#include "CompareNormSubState.h"

#include "Game.h"
#include "InputManager.h"
#include "DetailResultSubState.h"

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
		gameObjectManager.getObject<PictureObject>("NEXT").appear();
	}

	//�A�j���[�V�����X�V
	if (clearPictureFrame < 20) {
		GameObject& clearPicture = gameObjectManager.getObject<PictureObject>(clearPictureName);
		clearPicture.setObjectPosition({
			448 - (20 - clearPictureFrame) * 50,
			590
			});
		clearPicture.appear();
		clearPictureFrame++;
	}

	//���փ{�^������
	PictureObject& nextButton = gameObjectManager.getObject<PictureObject>("NEXT");
	InputManager& inputManager = game.getInputManager();
	if (inputManager.isClicked(nextButton)) {
		//���փ{�^���������ꂽ
		owner.changeSubState(new DetailResultSubState(owner, owner.getResult()));
		return;
	}


}

void CompareNormSubState::enter(Game& game)
{
	gameObjectManager.getObject<PictureObject>("KEKKAHAPPYOU").appear();
	gameObjectManager.getObject<TextObject>("BALLS").appear();
	gameObjectManager.getObject<TextObject>("NORM").appear();
	gameObjectManager.getObject<TextObject>("RUNS").appear();
	gameObjectManager.getObject<TextObject>("PITCHERNAME").appear();
}

void CompareNormSubState::exit(Game& game)
{
	gameObjectManager.getObject<PictureObject>("KEKKAHAPPYOU").hide();
	gameObjectManager.getObject<TextObject>("BALLS").hide();
	gameObjectManager.getObject<TextObject>("NORM").hide();
	gameObjectManager.getObject<TextObject>("RUNS").hide();
	gameObjectManager.getObject<TextObject>("PITCHERNAME").hide();
}