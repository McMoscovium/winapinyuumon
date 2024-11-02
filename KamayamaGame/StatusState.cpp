#include "StatusState.h"

#include "Game.h"
#include "InputManager.h"

#include "TitleScreenState.h"
#include "PlayingState.h"
#include <Windows.h>

StatusState::StatusState()
{
	//�C���X�^���X����
	appendObject(L"BUTTON_CHEAT", L".//assets//�`�[�g.bmp", { 256,128 });
	appendObject(L"BUTTON_START", L".//assets//�͂��߂�.bmp", { 256,128 });

	gameObjects.at(L"BUTTON_CHEAT")->setObjectPosition({ 800,500 });
	gameObjects.at(L"BUTTON_START")->setObjectPosition({ 100,500 });

	OutputDebugString(L"StatusState�̃C���X�^���X���쐬����܂���\n");
}

void StatusState::update(Game* game, InputManager* inputManager)
{
	//�`�[�g�{�^���N���b�N��
	if (isClicked(L"BUTTON_CHEAT", inputManager)) {
		OutputDebugString(L"�`�[�g�{�^�����N���b�N���ꂽ\n");
		game->changeState(new TitleScreenState());
		return;
	}

	//�X�^�[�g�{�^���N���b�N��
	if (isClicked(L"BUTTON_START", inputManager)) {
		OutputDebugString(L"�X�^�[�g�{�^���������ꂽ\n");
		game->changeState(new PlayingState());
		return;
	}
}
