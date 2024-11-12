#include "AfterBallLandingSubState.h"

#include "WaitingPitchingSubState.h"
#include "TextObject.h"

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
	//”ò‹——£‚ð•\Ž¦
	TextObject* distanceText = static_cast<TextObject*>(owner.getGameObjectPtr(L"TEXT_DISTANCE"));
	const int distance = owner.getDistance() / 20;
	std::wstring distanceTxt = L"”ò‹——£ : " + std::to_wstring(distance) + L" m";
	distanceText->setText(distanceTxt);
	distanceText->appear();
}

void AfterBallLandingSubState::exit(Game& game)
{
	GameObject& distanceText = owner.getGameObject(L"TEXT_DISTANCE");
	distanceText.hide();
}
