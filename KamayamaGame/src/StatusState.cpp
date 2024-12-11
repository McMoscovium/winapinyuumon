#include "GameState/StatusState/StatusState.h"

#include "GameState/GameState.h"
#include "Game/Game.h"
#include "Game/InputManager.h"
#include "GameObject/GameObject.h"
#include "GameObject/HatimituMeterObject.h"
#include "GameObject/GameObjectManager.h"

#include "GameState/TitleScreenState/TitleScreenState.h"
#include "GameState/PlayingState/PlayingState.h"
#include <Windows.h>
#include "GameObject/PictureObject.h"

#include "resource.h"

StatusState::StatusState(Game& game) :
	GameState<StatusState, GameSubState<StatusState>>(game)
{
	HINSTANCE hInstance = game.getHInstance();

	//�C���X�^���X����
	gameObjectManager.addFront<PictureObject>("CHEAT", IDB_BITMAP20, hInstance, SIZE{ 256,128 });
	gameObjectManager.addFront<PictureObject>("START", IDB_BITMAP21, hInstance, SIZE{ 256,128 });
	gameObjectManager.addFront<HatimituMeterObject>("HATIMITUMETER", IDB_BITMAP23, hInstance,  SIZE{ 49,45 });

	//�ʒu�ݒ�
	gameObjectManager.getObject<HatimituMeterObject>("HATIMITUMETER").setObjectPosition({ 200,200 });
	gameObjectManager.getObject<PictureObject>("CHEAT").setObjectPosition({ 800,500 });
	gameObjectManager.getObject<PictureObject>("START").setObjectPosition({ 100,500 });

	gameObjectManager.getObject<HatimituMeterObject>("HATIMITUMETER").setValue(5);

	showAll();

	OutputDebugString(L"StatusState�̃C���X�^���X���쐬����܂���\n");
}

void StatusState::update(Game& game)
{
	InputManager& inputManager = game.getInputManager();
	PictureObject& cheatButton = gameObjectManager.getObject<PictureObject>("CHEAT");

	//�`�[�g�{�^���N���b�N��
	if (inputManager.isClicked(cheatButton)) {
		OutputDebugString(L"�`�[�g�{�^�����N���b�N���ꂽ\n");
		game.changeState(new TitleScreenState(game));
		return;
	}
}
