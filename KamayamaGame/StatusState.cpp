#include "StatusState.h"

#include "Game.h"
#include "InputManager.h"

#include "TitleScreenState.h"
#include "PlayingState.h"
#include <Windows.h>

StatusState::StatusState()
{
	//インスタンス生成
	appendObject(L"BUTTON_CHEAT", L".//assets//チート.bmp", { 256,128 });
	appendObject(L"BUTTON_START", L".//assets//はじめる.bmp", { 256,128 });

	gameObjects.at(L"BUTTON_CHEAT")->setObjectPosition({ 800,500 });
	gameObjects.at(L"BUTTON_START")->setObjectPosition({ 100,500 });

	OutputDebugString(L"StatusStateのインスタンスが作成されました\n");
}

void StatusState::update(Game* game, InputManager* inputManager)
{
	//チートボタンクリック時
	if (isClicked(L"BUTTON_CHEAT", inputManager)) {
		OutputDebugString(L"チートボタンがクリックされた\n");
		game->changeState(new TitleScreenState());
		return;
	}

	//スタートボタンクリック時
	if (isClicked(L"BUTTON_START", inputManager)) {
		OutputDebugString(L"スタートボタンが押された\n");
		game->changeState(new PlayingState());
		return;
	}
}
