#include "AfterMeetSubState.h"

#include "PlayingState.h"
#include "Game.h"
#include "GameObject.h"
#include "Window.h"
#include "WaitingPitchingSubState.h"
#include "InputManager.h"
#include "TitleScreenState.h"

AfterMeetSubState::AfterMeetSubState(PlayingState& owner) :
	GameSubState<PlayingState>(owner)
{
}

void AfterMeetSubState::update(Game& game)
{
	//ボールが画面外に出たらchangeSubstate
	GameObject& ballObject = owner.getGameObject(L"PICTURE_BALL");
	Window* window = game.getWindow();
	if (ballObject.isOutOfClientRect(window)) {
		owner.changeSubState(new WaitingPitchingSubState(owner));
		return;
	}

	//終了ボタン処理
	InputManager& inputManager = game.getInputManager();
	GameObject& exitButton = owner.getGameObject(L"BUTTON_EXIT");
	if (inputManager.isClicked(exitButton)) {
		exit(game);//終了処理
		game.changeState(new TitleScreenState(game));
		return;
	}

	//バッター位置、見た目の更新
	owner.updateBatterPos(inputManager);
	owner.updateBatterAnimation(inputManager);

	//ボール位置の更新
	updateBall();
}

void AfterMeetSubState::updateBall()
{
	GameObject& ballObject = owner.getGameObject(L"PICTURE_BALL");
	POINT currentPos = ballObject.getPosition();
	const Ball& owner.getBall();
}
