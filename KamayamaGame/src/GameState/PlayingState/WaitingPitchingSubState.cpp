#include "GameState/PlayingState/WaitingPitchingSubState.h"

#include "Game/InputManager.h"
#include "Game/Game.h"
#include "GameState/GameState.h"
#include "GameState/PlayingState/InPitchingSubState.h"
#include "GameState/TitleScreenState/TitleScreenState.h"
#include "GameState/PlayingState/PlayingState.h"
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
	if (timer.span() > 1000) {
		owner.changeSubState(new InPitchingSubState(owner));
		return;
	}

	//終了ボタン処理
	PictureObject& exitButton = gameObjectManager.getObject<PictureObject>("EXIT");
	if (inputManager.isClicked(exitButton)) {
		game.changeState(new TitleScreenState(game, owner.getAudioManager()));
		return;
	}

	//入力に応じてバッターのアニメーションを更新
	owner.updateBatterPos(inputManager);
	owner.updateBatterAnimation(inputManager);
	int currentBatterFrame = gameObjectManager.getObject<PictureObject>("BATTER").getCurrentFrameNumber();
	if (2 <= currentBatterFrame && currentBatterFrame <= 4) {
		owner.updateBatFrame(currentBatterFrame);
	}

	if (currentBatterFrame >= 5) {
		//バット判定枠の消去
		gameObjectManager.getObject<PictureObject>("BAT_HITBOX").hide();
	}
}

void WaitingPitchingSubState::enter(Game& game)
{
	gameObjectManager.getObject<PictureObject>("FIELD").appear();
	GameObject& batter = gameObjectManager.getObject<PictureObject>("BATTER");
	InputManager& inputManager = game.getInputManager();
	POINT mouse = inputManager.getMousePosition();
	owner.setBatterInBox(mouse);
	batter.changeSizeRate(1.0f);
	batter.appear();
	
	gameObjectManager.getObject<PictureObject>("EXIT").appear();
	
	GameObject& pitcher = gameObjectManager.getObject<PictureObject>("PITCHER");
	pitcher.changeSizeRate(0.5f);
	pitcher.setObjectPosition({ 519,5 });
	pitcher.appear();

	TextObject& normText = gameObjectManager.getObject<TextObject>("NORM");
	TextObject& runsText = gameObjectManager.getObject<TextObject>("RUNS");
	TextObject& restText = gameObjectManager.getObject<TextObject>("REST");
	normText.appear();
	runsText.appear();
	restText.appear();
}

void WaitingPitchingSubState::exit(Game& game)
{
}
