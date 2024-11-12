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
	timer.setRecord();//�T�u�X�e�[�g�J�n�������L�^
}

void WaitingPitchingSubState::update(Game & game)
{
	InputManager& inputManager = game.getInputManager();
	timer.update();

	//�T�u�X�e�[�g�J�n��2000ms�o�߂�����s�b�`���O�J�n
	if (timer.span() > 2000) {
		owner.changeSubState(new InPitchingSubState(owner));
		return;
	}

	//�I���{�^������
	GameObject& exitButton = owner.getGameObject(L"BUTTON_EXIT");
	if (inputManager.isClicked(exitButton)) {
		game.changeState(new TitleScreenState(game));
		return;
	}

	//���͂ɉ����ăo�b�^�[�̃A�j���[�V�������X�V
	owner.updateBatterPos(inputManager);
	owner.updateBatterAnimation(inputManager);
	int currentBatterFrame = owner.getGameObject(L"PICTURE_BATTER").getCurrentFrameNumber();
	if (2 <= currentBatterFrame && currentBatterFrame <= 4) {
		owner.updateBatFrame(currentBatterFrame);
	}


	if (currentBatterFrame >= 5) {
		//�o�b�g����g�̏���
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
