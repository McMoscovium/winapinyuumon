#include "StatusState.h"

#include "Game.h"
#include "InputManager.h"

#include "TitleScreenState.h"
#include "PlayingState.h"
#include <Windows.h>
#include <memory>

using namespace std;


StatusState::StatusState(Game& game):
	GameState(game)
{
	//�C���X�^���X����
	appendObjectFromFile(L"BUTTON_CHEAT", L".//assets//�`�[�g.bmp", { 256,128 });
	appendObjectFromFile(L"BUTTON_START", L".//assets//�͂��߂�.bmp", { 256,128 });

	gameObjects.at(L"BUTTON_CHEAT").setPosition({ 800,500 });
	gameObjects.at(L"BUTTON_START").setPosition({ 100,500 });

	OutputDebugString(L"StatusState�̃C���X�^���X���쐬����܂���\n");
}

void StatusState::update()
{
	const InputManager& inputManager = game.getConstInputManager();

	//�`�[�g�{�^���N���b�N��
	GameObject& cheatButton = getGameObject(L"BUTTON_CHEAT");
	if (inputManager.isClicked(cheatButton)) {
		OutputDebugString(L"�`�[�g�{�^�����N���b�N���ꂽ\n");
		game.changeState(make_unique<TitleScreenState>(game));
		return;
	}

	//�X�^�[�g�{�^���N���b�N��
	GameObject& startButton = getGameObject(L"BUTTON_START");
	if (inputManager.isClicked(startButton)) {
		OutputDebugString(L"�X�^�[�g�{�^���������ꂽ\n");
		game.changeState(make_unique<PlayingState>(game));
		return;
	}
}