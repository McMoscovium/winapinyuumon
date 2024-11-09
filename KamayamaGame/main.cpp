#include <Windows.h>
#include "Window.h"
#include "Game.h"
#include "InputManager.h"
#include <memory>
#include "TitleScreenState.h"

using namespace std;

//開発用
#include <iostream>

const LPCWSTR gameName = L"クマの釜山のホームランダービー！";


void mainLoop(Window& window);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInst,
	LPSTR lpszCmdLine,
	int nShowCmd) {


	//初期化パート
	//必要なインスタンスを作成、初期化
	Game game = Game();
	Window window(hInstance, nShowCmd, &game);

	unique_ptr<TitleScreenState> newState = make_unique<TitleScreenState>(game);
	

	//初期画面レンダリング
	window.render(game.getCurrentState());
	//初期画面表示
	window.show();
	mainLoop(window);

	//終了処理
	//WM_QUITメッセージがもう出されているので、はやく終わる。
	window.termination();
	game.termination();

	return 0;
}

void mainLoop(Window& window) {
	while (window.update()) {// WM_QUITメッセージが受信されたらループを終了
	}
	//WM_QUITを受け取るとループを抜ける
}