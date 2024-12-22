#include "GameState/PlayingState/EndPlayingSubState.h"

#include "Game/Game.h"
#include "GameState/PlayResultState/PlayResultState.h"
#include "Stage/Stage.h"

void EndPlayingSubState::update(Game& game)
{
	timer.update();
	//2000ms‚½‚Á‚½‚çchangeState
	if (timer.span() > 2000) {
		Stage* stage = owner.getStage();
		game.changeState(new PlayResultState(
			game,
			owner.getAudioManager(),
			owner.getResult(), 
			stage->getTrials(),
			stage->getNorm(),
			stage->pitcherName,
			stage->stageNumber,
			stage->scoreFactor
			));
		return;
	}
}

void EndPlayingSubState::enter(Game& game)
{
	timer.setRecord();
	GameObject& finish = gameObjectManager.getObject<PictureObject>("FINISH");
	finish.setObjectPosition({ 313,282 });
	finish.appear();
	OutputDebugString(L"Entering EndPlayingSubState\n");
}

void EndPlayingSubState::exit(Game& game)
{
	OutputDebugString(L"Exitting EndPlayingSubState\n");
}
