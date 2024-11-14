#include "EndPlayingSubState.h"

#include "Game.h"
#include "PlayResultState.h"

void EndPlayingSubState::update(Game& game)
{
	//2000ms‚½‚Á‚½‚çchangeState
	if (timer.span() > 2000) {
		game.changeState(new PlayResultState(game, owner.getResult()));
		return;
	}
}

void EndPlayingSubState::enter(Game& game)
{
	timer.setRecord();
	GameObject& finish = owner.getGameObject(L"PICTURE_FINISH");
	finish.setObjectPosition({ 313,282 });
	finish.appear();
}

void EndPlayingSubState::exit(Game& game)
{
}
