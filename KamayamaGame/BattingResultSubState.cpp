#include "BattingResultSubState.h"

#include "WaitingPitchingSubState.h"
#include "TextObject.h"
#include "EndPlayingSubState.h"
#include "Game.h"
#include "Result.h"

std::wstring BattingResultSubState::resultString() const
{
	switch (result) {
	case PlayingState::HOMERUN:
		return L"ホームラン";
	case PlayingState::HIT:
		return L"ヒット";
	case PlayingState::FOUL:
		return L"ファール";
	case PlayingState::STRIKE:
		return L"ストライク";
	default:
		return L"結果無し";
	}
}

void BattingResultSubState::update(Game& game)
{
	//result=STRIKEならバッターはマウスに合わせて動く
	if (result == PlayingState::STRIKE) {
		owner.updateBatterPos(game.getInputManager());
		owner.updateBatterAnimation(game.getInputManager());
	}

	//1000msたったらchangeState処理
	timer.update();
	if (timer.span() < 1000) {
		return;
	}

	//1000msたった
	//打った球数がowner.trialsに達したらchangeState
	if (owner.getRestBalls() <= 0) {
		owner.changeSubState(new EndPlayingSubState(owner));
		return;
	}
	owner.changeSubState(new WaitingPitchingSubState(owner));
	return;
	
}

void BattingResultSubState::enter(Game& game)
{
	//ボタンを消す
	owner.getGameObject(L"BUTTON_EXIT").hide();
	timer.setRecord();

	//Resultを更新
	const int distance= owner.getDistance() / 20;
	owner.getResult().update(distance, result == PlayingState::HOMERUN);

	if (result != PlayingState::STRIKE) {
		//飛距離を表示
		TextObject* distanceText = static_cast<TextObject*>(owner.getGameObjectPtr(L"TEXT_DISTANCE"));
		std::wstring distanceTxt = L"飞距离 : " + std::to_wstring(distance) + L" m";
		distanceText->setText(distanceTxt);
		distanceText->setFont(L"NSimSun");
		distanceText->setObjectPosition({ 231,353 });
		distanceText->appear();

	}
	

	//結果を表示
	TextObject* resultText = (TextObject*)(owner.getGameObjectPtr(L"TEXT_RESULT"));
	resultText->setText(resultString());
	resultText->setFont(TEXT("HG行書体"));
	resultText->setObjectPosition({ 382,184 });
	resultText->appear();
}

void BattingResultSubState::exit(Game& game)
{
	GameObject& resultText = owner.getGameObject(L"TEXT_RESULT");
	resultText.hide();
	GameObject& distanceText = owner.getGameObject(L"TEXT_DISTANCE");
	distanceText.hide();
}
