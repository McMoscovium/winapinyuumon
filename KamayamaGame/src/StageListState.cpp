#include "GameState/StageListState/StageListState.h"

#include "Game/Game.h"
#include "GameObject/PictureObject.h"
#include "Game/InputManager.h"
#include "GameState/TitleScreenState/TitleScreenState.h"
#include "GameState/PlayingState/PlayingState.h"
#include "Stage/TintinStage.h"
#include "Stage/SasakiStage.h"
#include "resource.h"

StageListState::StageListState(Game& game):
	GameState(game)
{
	HINSTANCE hInstance = game.getHInstance();

	PictureObject& back = gameObjectManager.addFront<PictureObject>("BACK", IDB_BITMAP14,hInstance, SIZE{ 1152,720 });
	gameObjectManager.addFront<PictureObject>("TO_TITLE", IDB_BITMAP18, hInstance, SIZE{ 192,68 });
	gameObjectManager.addFront<PictureObject>("TINTIN", IDB_BITMAP5, hInstance, SIZE{ 207,252 });
	gameObjectManager.addFront<PictureObject>("STAGE1", IDB_BITMAP3, hInstance, SIZE{ 162,41 });
	gameObjectManager.addFront<PictureObject>("STAGE2", IDB_BITMAP4, hInstance, SIZE{ 162,41 });

	PictureObject& toTitleButton = gameObjectManager.getObject<PictureObject>("TO_TITLE");
	toTitleButton.setObjectPosition({ 47,574 });
	GameObject& tintin =
		gameObjectManager.getObject<GameObject>("TINTIN");
	tintin.setObjectPosition({ 44,125 });
	PictureObject& stage1Button = gameObjectManager.getObject<PictureObject>("STAGE1");
	stage1Button.setObjectPosition({ 44,400 });
	PictureObject& stage2Button = gameObjectManager.getObject<PictureObject>("STAGE2");
	stage2Button.setObjectPosition({ 444,400 });
	

	back.appear();
	toTitleButton.appear();
	tintin.appear();
	stage1Button.appear();
	stage2Button.appear();
}

void StageListState::update(Game& game)
{
	InputManager& inputManager = game.getInputManager();
	PictureObject& toTitleButton = gameObjectManager.getObject<PictureObject>("TO_TITLE");

	//タイトルヘボタン処理
	if (inputManager.isClicked(toTitleButton)) {
		game.changeState(new TitleScreenState(game));
		return;
	}

	PictureObject& stage1Button = gameObjectManager.getObject<PictureObject>("STAGE1");
	PictureObject& stage2Button = gameObjectManager.getObject<PictureObject>("STAGE2");
	//ステージ選択ボタン処理
	if (inputManager.isClicked(stage1Button)) {
		game.changeState(new PlayingState(game, new TintinStage()));
	}

	if (inputManager.isClicked(stage2Button)) {
		game.changeState(new PlayingState(game, new SasakiStage()));
	}
}
