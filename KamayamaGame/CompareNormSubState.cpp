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
		gameObjectManager.getObject<PictureObject>("NEXT").appear();
	}

	//アニメーション更新
	if (clearPictureFrame < 20) {
		GameObject& clearPicture = gameObjectManager.getObject<PictureObject>(clearPictureName);
		clearPicture.setObjectPosition({
			448 - (20 - clearPictureFrame) * 50,
			590
			});
		clearPicture.appear();
		clearPictureFrame++;
	}

	//次へボタン処理
	PictureObject& nextButton = gameObjectManager.getObject<PictureObject>("NEXT");
	InputManager& inputManager = game.getInputManager();
	if (inputManager.isClicked(nextButton)) {
		//次へボタンが押された
		OutputDebugString(L"次へボタンが押された\n");
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
}
