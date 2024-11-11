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
	//�{�[������ʊO�ɏo����changeSubstate
	GameObject& ballObject = owner.getGameObject(L"PICTURE_BALL");
	Window* window = game.getWindow();
	if (ballObject.isOutOfClientRect(window)) {
		owner.changeSubState(new WaitingPitchingSubState(owner));
		return;
	}

	//�I���{�^������
	InputManager& inputManager = game.getInputManager();
	GameObject& exitButton = owner.getGameObject(L"BUTTON_EXIT");
	if (inputManager.isClicked(exitButton)) {
		exit(game);//�I������
		game.changeState(new TitleScreenState(game));
		return;
	}

	//�o�b�^�[�ʒu�A�����ڂ̍X�V
	owner.updateBatterPos(inputManager);
	owner.updateBatterAnimation(inputManager);

	//�{�[���ʒu�̍X�V
	updateBall();
}

void AfterMeetSubState::updateBall()
{
	GameObject& ballObject = owner.getGameObject(L"PICTURE_BALL");
	POINT currentPos = ballObject.getPosition();
	const Ball& owner.getBall();
}
