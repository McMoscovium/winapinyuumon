#include "StatusState.h"

#include "GameState.h"
#include "Game.h"
#include "InputManager.h"
#include "GameObject.h"
#include "HatimituMeterObject.h"

#include "TitleScreenState.h"
#include "PlayingState.h"
#include <Windows.h>

StatusState::StatusState(Game& game) :
	GameState<StatusState,GameSubState<StatusState>>(game),
	hatimituMeter(HatimituMeter())
{
	//インスタンス生成
	appendObject(L"BUTTON_CHEAT", L".//assets//チート.bmp", { 256,128 });
	appendObject(L"BUTTON_START", L".//assets//はじめる.bmp", { 256,128 });
	gameObjects.emplace(L"HATIMITUMETER", hatimituMeter.getObjPtr());
	objectOrder.push_back(L"HATIMITUMETER");

	getGameObject(L"HATIMITUMETER").setObjectPosition({ 200,200 });
	getGameObject(L"BUTTON_CHEAT").setObjectPosition({ 800,500 });
	getGameObject(L"BUTTON_START").setObjectPosition({ 100,500 });

	hatimituMeter.setValue(5);

	showAll();

	OutputDebugString(L"StatusStateのインスタンスが作成されました\n");
}

void StatusState::update(Game& game)
{
	InputManager& inputManager = game.getInputManager();
	
	//チートボタンクリック時
	GameObject& cheatButton = getGameObject(L"BUTTON_CHEAT");
	if (inputManager.isClicked(cheatButton)) {
		OutputDebugString(L"チートボタンがクリックされた\n");
		game.changeState(new TitleScreenState(game));
		return;
	}
}
