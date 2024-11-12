#include "WaitingPitchingSubState.h"

#include "InputManager.h"
#include "Game.h"
#include "GameState.h"
#include "InPitchingSubState.h"
#include "TitleScreenState.h"
#include "PlayingState.h"
#include <Windows.h>

WaitingPitchingSubState::WaitingPitchingSubState(PlayingState& gameState) :
	GameSubState(gameState)
{
	timer.setRecord();//サブステート開始時刻を記録
}

void WaitingPitchingSubState::update(Game & game)
{
	InputManager& inputManager = game.getInputManager();
	timer.update();

	//サブステート開始後2000ms経過したらピッチング開始
	if (timer.span() > 2000) {
		owner.changeSubState(new InPitchingSubState(owner));
		return;
	}

	//終了ボタン処理
	GameObject& exitButton = owner.getGameObject(L"BUTTON_EXIT");
	if (inputManager.isClicked(exitButton)) {
		game.changeState(new TitleScreenState(game));
		return;
	}

	//入力に応じてバッターのアニメーションを更新
	owner.updateBatterPos(inputManager);
	owner.updateBatterAnimation(inputManager);
	int currentBatterFrame = owner.getGameObject(L"PICTURE_BATTER").getCurrentFrameNumber();
	if (2 <= currentBatterFrame && currentBatterFrame <= 4) {
		owner.updateBatFrame(currentBatterFrame);
	}


	if (currentBatterFrame >= 5) {
		//バット判定枠の消去
		owner.getGameObject(L"JUDGE_BAT").hide();
	}
}

void WaitingPitchingSubState::enter(Game& game)
{
	OutputDebugString(L"Entering WaitingPitchingSubState\n");
	owner.getGameObject(L"PICTURE_FIELD").appear();
	owner.getGameObject(L"PICTURE_BATTER").appear();
	owner.getGameObject(L"BUTTON_EXIT").appear();
	owner.getGameObject(L"PICTURE_PITCHER").appear();

	GameObject& pitcher = owner.getGameObject(L"PICTURE_PITCHER");
	pitcher.changeSizeRate(0.5);
	pitcher.setObjectPosition({ 519,5 });
}

void WaitingPitchingSubState::exit(Game& game)
{
	OutputDebugString(L"Exitting WaitingPitchingSubState\n");
}
