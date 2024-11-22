#include "StageListState.h"

#include "Game.h"
#include "PictureObject.h"
#include "InputManager.h"
#include "TitleScreenState.h"
#include "PlayingState.h"
#include "TintinStage.h"
#include "SasakiStage.h"

StageListState::StageListState(Game& game):
	GameState(game)
{
	PictureObject& back = gameObjectManager.addFront<PictureObject>("BACK", L".//assets//ステージセレクト.bmp", SIZE{ 1152,720 });
	gameObjectManager.addFront<PictureObject>("TO_TITLE", L".//assets//タイトルヘ.bmp", SIZE{ 192,68 });
	gameObjectManager.addFront<PictureObject>("TINTIN", L".//assets//tintin選択.bmp", SIZE{ 207,252 });
	gameObjectManager.addFront<PictureObject>("STAGE1", L".//assets//Stage1.bmp", SIZE{ 162,41 });
	gameObjectManager.addFront<PictureObject>("STAGE2", L".//assets//Stage2.bmp", SIZE{ 162,41 });

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
