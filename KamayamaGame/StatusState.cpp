#include "StatusState.h"

#include "GameState.h"
#include "Game.h"
#include "InputManager.h"
#include "GameObject.h"
#include "HatimituMeterObject.h"
#include "GameObjectManager.h"

#include "TitleScreenState.h"
#include "PlayingState.h"
#include <Windows.h>
#include "PictureObject.h"

StatusState::StatusState(Game& game) :
	GameState<StatusState, GameSubState<StatusState>>(game)
{
	//インスタンス生成
	gameObjectManager.addFront<PictureObject>("CHEAT", L".//assets//チート.bmp", SIZE{ 256,128 });
	gameObjectManager.addFront<PictureObject>("START", L".//assets//はじめる.bmp", SIZE{ 256,128 });
	gameObjectManager.addFront<HatimituMeterObject>("HATIMITUMETER", L".//assets//はちみつ.bmp", SIZE{ 49,45 });

	//位置設定
	gameObjectManager.getObject<HatimituMeterObject>("HATIMITUMETER").setObjectPosition({ 200,200 });
	gameObjectManager.getObject<PictureObject>("CHEAT").setObjectPosition({ 800,500 });
	gameObjectManager.getObject<PictureObject>("START").setObjectPosition({ 100,500 });

	gameObjectManager.getObject<HatimituMeterObject>("HATIMITUMETER").setValue(5);

	showAll();

	OutputDebugString(L"StatusStateのインスタンスが作成されました\n");
}

void StatusState::update(Game& game)
{
	InputManager& inputManager = game.getInputManager();
	PictureObject& cheatButton = gameObjectManager.getObject<PictureObject>("CHEAT");

	//チートボタンクリック時
	if (inputManager.isClicked(cheatButton)) {
		OutputDebugString(L"チートボタンがクリックされた\n");
		game.changeState(new TitleScreenState(game));
		return;
	}
}
