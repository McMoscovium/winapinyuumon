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
	//インスタンス生成
	appendObjectFromFile(L"BUTTON_CHEAT", L".//assets//チート.bmp", { 256,128 });
	appendObjectFromFile(L"BUTTON_START", L".//assets//はじめる.bmp", { 256,128 });

	gameObjects.at(L"BUTTON_CHEAT").setPosition({ 800,500 });
	gameObjects.at(L"BUTTON_START").setPosition({ 100,500 });

	OutputDebugString(L"StatusStateのインスタンスが作成されました\n");
}

void StatusState::update()
{
	const InputManager& inputManager = game.getConstInputManager();

	//チートボタンクリック時
	GameObject& cheatButton = getGameObject(L"BUTTON_CHEAT");
	if (inputManager.isClicked(cheatButton)) {
		OutputDebugString(L"チートボタンがクリックされた\n");
		game.changeState(make_unique<TitleScreenState>(game));
		return;
	}

	//スタートボタンクリック時
	GameObject& startButton = getGameObject(L"BUTTON_START");
	if (inputManager.isClicked(startButton)) {
		OutputDebugString(L"スタートボタンが押された\n");
		game.changeState(make_unique<PlayingState>(game));
		return;
	}
}