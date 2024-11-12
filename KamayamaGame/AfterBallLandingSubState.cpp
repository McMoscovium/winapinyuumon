#include "AfterBallLandingSubState.h"

#include "WaitingPitchingSubState.h"

void AfterBallLandingSubState::update(Game& game)
{
	//2000ms‚½‚Á‚½‚çchangeState
	timer.update();
	if (timer.span() > 1000) {
		owner.changeSubState(new WaitingPitchingSubState(owner));
		return;
	}
}

void AfterBallLandingSubState::enter(Game& game)
{
	timer.setRecord();
}

void AfterBallLandingSubState::exit(Game& game)
{
}
