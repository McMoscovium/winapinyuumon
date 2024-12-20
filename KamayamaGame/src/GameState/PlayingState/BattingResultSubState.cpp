#include "GameState/PlayingState/BattingResultSubState.h"

#include "GameState/PlayingState/WaitingPitchingSubState.h"
#include "GameObject/TextObject.h"
#include "GameState/PlayingState/EndPlayingSubState.h"
#include "Game/Game.h"
#include "util/Result.h"

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
	gameObjectManager.getObject<PictureObject>("EXIT").hide();
	timer.setRecord();

	bool isHomeRun = result==PlayingState::HOMERUN;

	

	//Resultを更新
	const int distance= owner.getDistance() / 20;
	owner.getResult().update(distance, isHomeRun);

	//画面上の数字更新
	TextObject& runsText = gameObjectManager.getObject<TextObject>("RUNS");
	TextObject& restText = gameObjectManager.getObject<TextObject>("REST");
	runsText.setText(std::to_wstring(owner.getResult().getRuns()));
	restText.setText(std::to_wstring(owner.getRestBalls()));

	if (result != PlayingState::STRIKE) {
		//飛距離を表示
		TextObject& distanceText = static_cast<TextObject&>(gameObjectManager.getObject<TextObject>("DISTANCE"));
		std::wstring distanceTxt = L"飞距离 : " + std::to_wstring(distance) + L" m";
		distanceText.setText(distanceTxt);
		distanceText.setFont(L"NSimSun");
		distanceText.setObjectPosition({ 231,353 });
		distanceText.appear();

	}
	

	//結果を表示
	TextObject& resultText = (TextObject&)(gameObjectManager.getObject<TextObject>("RESULT"));
	resultText.setText(resultString());
	resultText.setFont(TEXT("HG行書体"));
	resultText.setObjectPosition({ 382,184 });
	resultText.appear();
}

void BattingResultSubState::exit(Game& game)
{
	GameObject& resultText = gameObjectManager.getObject<TextObject>("RESULT");
	resultText.hide();
	GameObject& distanceText = gameObjectManager.getObject<TextObject>("DISTANCE");
	distanceText.hide();
}
