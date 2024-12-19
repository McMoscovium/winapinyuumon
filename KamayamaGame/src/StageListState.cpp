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
	gameObjectManager.addFront<PictureObject>("LOAD_ANIMATION", IDB_BITMAP38, hInstance, SIZE{ 200,266 });

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

	changeSubState(new ChoiceSubState(*this));
}

void StageListState::update(Game& game)
{
	currentSubState->update(game);
}

void StageListState::enter(Game& game)
{
	audioManager.continueLoop("100ACRE");
}

void StageListState::exit(Game& game)
{
}
