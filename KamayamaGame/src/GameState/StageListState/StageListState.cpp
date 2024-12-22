#include "GameState/StageListState/StageListState.h"

#include "Game/Game.h"
#include "GameObject/PictureObject.h"
#include "GameState/StageListState/ChoiceSubState.h"
#include "GameState/PlayingState/PlayingState.h"
#include "resource.h"

StageListState::StageListState(Game& game, AudioManager& audioManager):
	GameState(game, audioManager)
{
	HINSTANCE hInstance = game.getHInstance();

	PictureObject& back = gameObjectManager.addFront<PictureObject>("BACK", IDB_BITMAP14,hInstance, SIZE{ 1152,720 });
	gameObjectManager.addFront<PictureObject>("TO_TITLE", IDB_BITMAP18, hInstance, SIZE{ 192,68 });
	gameObjectManager.addFront<PictureObject>("TINTIN", IDB_BITMAP5, hInstance, SIZE{ 207,252 });
	gameObjectManager.addFront<PictureObject>("STAGE1", IDB_BITMAP3, hInstance, SIZE{ 162,41 });
	gameObjectManager.addFront<PictureObject>("STAGE2", IDB_BITMAP4, hInstance, SIZE{ 162,41 });
	gameObjectManager.addFront<PictureObject>("STAGE3", IDB_BITMAP52, hInstance, SIZE{ 162,41 });
	gameObjectManager.addFront<PictureObject>("STAGE4", IDB_BITMAP53, hInstance, SIZE{ 162,41 });
	gameObjectManager.addFront<PictureObject>("STAGE5", IDB_BITMAP54, hInstance, SIZE{ 162,41 });
	gameObjectManager.addFront<PictureObject>("STAGE6", IDB_BITMAP55, hInstance, SIZE{ 162,41 });
	gameObjectManager.addFront<PictureObject>("STAGE7", IDB_BITMAP56, hInstance, SIZE{ 162,41 });
	gameObjectManager.addFront<PictureObject>("STAGE8", IDB_BITMAP57, hInstance, SIZE{ 200,70 });
	gameObjectManager.addFront<PictureObject>("LOAD_ANIMATION", IDB_BITMAP38, hInstance, SIZE{ 200,266 });

	PictureObject& toTitleButton = gameObjectManager.getObject<PictureObject>("TO_TITLE");
	toTitleButton.setObjectPosition({ 20,652 });
	GameObject& tintin =
		gameObjectManager.getObject<GameObject>("TINTIN");
	tintin.setObjectPosition({ 240,95 });
	PictureObject& stage1Button = gameObjectManager.getObject<PictureObject>("STAGE1");
	stage1Button.setObjectPosition({ 269,300 });
	PictureObject& stage2Button = gameObjectManager.getObject<PictureObject>("STAGE2");
	stage2Button.setObjectPosition({ 469,300 });
	PictureObject& stage3Button = gameObjectManager.getObject<PictureObject>("STAGE3");
	stage3Button.setObjectPosition({ 669,300 });
	PictureObject& stage4Button = gameObjectManager.getObject<PictureObject>("STAGE4");
	stage4Button.setObjectPosition({ 869,300 });
	PictureObject& stage5Button = gameObjectManager.getObject<PictureObject>("STAGE5");
	stage5Button.setObjectPosition({ 269,630 });
	PictureObject& stage6Button = gameObjectManager.getObject<PictureObject>("STAGE6");
	stage6Button.setObjectPosition({ 469,630 });
	PictureObject& stage7Button = gameObjectManager.getObject<PictureObject>("STAGE7");
	stage7Button.setObjectPosition({ 669,630 });
	PictureObject& stage8Button = gameObjectManager.getObject<PictureObject>("STAGE8");
	stage8Button.setObjectPosition({ 869,630 });
	

	back.appear();
	toTitleButton.appear();
	tintin.appear();
	stage1Button.appear();
	stage2Button.appear();
	stage3Button.appear();
	stage4Button.appear();
	stage5Button.appear();
	stage6Button.appear();
	stage7Button.appear();
	stage8Button.appear();

	changeSubState(new ChoiceSubState(*this));
}

void StageListState::update(Game& game)
{
	currentSubState->update(game);
}

void StageListState::enter(Game& game)
{
	audioManager.addWav("100ACRE", game.getHInstance(), IDR_WAVE4);
	audioManager.continueLoop("100ACRE", 132300, 2381400 - 132300);
}

void StageListState::exit(Game& game)
{
}
