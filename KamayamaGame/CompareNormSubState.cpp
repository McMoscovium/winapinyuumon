#include "CompareNormSubState.h"

#include "Game.h"
#include "InputManager.h"

void CompareNormSubState::update(Game& game)
{
	timer.update();
	//1500msたつまでまつ
	if (timer.span() < 1500) {
		return;
	}

	//以下、1500msたった

	//クリアアニメーションを表示し終える
	if (clearPictureFrame == 20) {
		owner.getGameObject(L"BUTTON_NEXT").appear();
	}

	//アニメーション更新
	if (clearPictureFrame < 20) {
		GameObject& clearPicture = owner.getGameObject(clearPictureName);
		clearPicture.setObjectPosition({
			448 - (20 - clearPictureFrame) * 50,
			590
			});
		clearPicture.appear();
		clearPictureFrame++;
	}

	//次へボタン処理
	GameObject& nextButton = owner.getGameObject(L"BUTTON_NEXT");
	InputManager& inputManager = game.getInputManager();
	if (inputManager.isClicked(nextButton)) {
		//次へボタンが押された
		OutputDebugString(L"次へボタンが押された\n");
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
