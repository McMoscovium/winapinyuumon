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
	PictureObject& exitButton = gameObjectManager.getObject<PictureObject>("EXIT");
	if (inputManager.isClicked(exitButton)) {
		game.changeState(new TitleScreenState(game));
		return;
	}

	//���͂ɉ����ăo�b�^�[�̃A�j���[�V�������X�V
	owner.updateBatterPos(inputManager);
	owner.updateBatterAnimation(inputManager);
	int currentBatterFrame = gameObjectManager.getObject<PictureObject>("BATTER").getCurrentFrameNumber();
	if (2 <= currentBatterFrame && currentBatterFrame <= 4) {
		owner.updateBatFrame(currentBatterFrame);
	}

	if (currentBatterFrame >= 5) {
		//�o�b�g����g�̏���
		gameObjectManager.getObject<PictureObject>("BAT_HITBOX").hide();
	}
}

void WaitingPitchingSubState::enter(Game& game)
{
	OutputDebugString(L"Entering WaitingPitchingSubState\n");
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
}

void WaitingPitchingSubState::exit(Game& game)
{
	OutputDebugString(L"Exitting WaitingPitchingSubState\n");
}