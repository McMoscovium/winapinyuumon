#include "DetailResultSubState.h"

#include "Game.h"
#include "InputManager.h"
#include "StageListState.h"

void DetailResultSubState::update(Game& game)
{
	InputManager& inputManager = game.getInputManager();
	//ステージ選択へボタン処理
	PictureObject& toStageList = gameObjectManager.getObject<PictureObject>("TO_STAGELIST");
	if (inputManager.isClicked(toStageList)) {
		game.changeState(new StageListState(game));
		return;
	}
}

void DetailResultSubState::enter(Game& game)
{
	PictureObject& back = gameObjectManager.getObject<PictureObject>("KEKKAHAPPYOU2");
	PictureObject& toStageList = gameObjectManager.getObject<PictureObject>("TO_STAGELIST");
	TextObject& runs = gameObjectManager.getObject<TextObject>("RUNS");
	TextObject& runStreak = gameObjectManager.getObject<TextObject>("RUNSTREAK");
	TextObject& maxDist = gameObjectManager.getObject<TextObject>("MAX_DISTANCE");
	TextObject& distanceSum = gameObjectManager.getObject<TextObject>("DISTANCE_SUM");
	TextObject& bonus = gameObjectManager.getObject<TextObject>("BONUS_POINT");

	runs.setObjectPosition({ 752,204 });
	runStreak.setObjectPosition({ 803,298 });
	maxDist.setObjectPosition({ 788,378 });
	distanceSum.setObjectPosition({ 720,456 });
	bonus.setObjectPosition({ 867,553 });

	back.appear();
	toStageList.appear();
	runs.appear();
	runStreak.appear();
	maxDist.appear();
	distanceSum.appear();
	bonus.appear();
}

void DetailResultSubState::exit(Game& game)
{
}
