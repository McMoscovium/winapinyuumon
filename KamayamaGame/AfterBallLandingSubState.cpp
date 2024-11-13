#include "AfterBallLandingSubState.h"

#include "WaitingPitchingSubState.h"
#include "TextObject.h"

std::wstring AfterBallLandingSubState::resultString() const
{
	switch (result) {
	case PlayingState::HOMERUN:
		return L"ホームラン";
	case PlayingState::HIT:
		return L"ヒット";
	case PlayingState::FOUL:
		return L"ファール";
	default:
		return L"結果無し";
	}
}

void AfterBallLandingSubState::update(Game& game)
{
	//2000msたったらchangeState
	timer.update();
	if (timer.span() > 1000) {
		owner.changeSubState(new WaitingPitchingSubState(owner));
		return;
	}
}

void AfterBallLandingSubState::enter(Game& game)
{
	timer.setRecord();
	//飛距離を表示
	TextObject* distanceText = static_cast<TextObject*>(owner.getGameObjectPtr(L"TEXT_DISTANCE"));
	const int distance = owner.getDistance() / 20;//表示用の距離（メートル）に直す
	std::wstring distanceTxt = L"飞距离 : " + std::to_wstring(distance) + L" m";
	distanceText->setText(distanceTxt);
	distanceText->setFont(L"NSimSun");
	distanceText->setObjectPosition({ 231,353 });
	distanceText->appear();

	//結果を表示
	TextObject* resultText = (TextObject*)(owner.getGameObjectPtr(L"TEXT_RESULT"));
	resultText->setText(resultString());
	resultText->setFont(TEXT("HG行書体"));
	resultText->setObjectPosition({ 382,184 });
	resultText->appear();
}

void AfterBallLandingSubState::exit(Game& game)
{
	GameObject& resultText = owner.getGameObject(L"TEXT_RESULT");
	resultText.hide();
	GameObject& distanceText = owner.getGameObject(L"TEXT_DISTANCE");
	distanceText.hide();
}
