#include <Windows.h>
#include "Window.h"
#include "Game.h"
#include "InputManager.h"

//開発用
#include <iostream>

const LPCWSTR gameName = L"クマの釜山のホームランダービー！";


void mainLoop(Game* game,Window* window,InputManager* inputManager);
void termination();

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInst,
	LPSTR lpszCmdLine,
	int nShowCmd) {

	//開発用コンソール
	// コンソールウィンドウを作成
	AllocConsole();

	// 標準出力をコンソールにリダイレクト
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);  // stdoutをコンソールにリダイレクト
	//以上開発用


	//初期化パート
	//必要なインスタンスを作成、初期化
	Game game;
	Window window(hInstance, nShowCmd);
	InputManager inputManager;

	//初期画面レンダリング
	window.render(&game);
	//初期画面表示
	window.show();

	//メインループ
	mainLoop(&game, &window, &inputManager);

	//開発用
	std::cout << "メインループ終了" << std::endl;

	//終了処理
	//WM_QUITメッセージがもう出されているので、はやく終わる。
	termination();

	// コンソールが自動で閉じないようにする
	std::cout << "Press Enter to exit...";
	std::cin.get();

	// コンソールを解放
	FreeConsole();

	return 0;
}

void mainLoop(Game* game,Window* window, InputManager* inputManager) {
	while (window->defaultUpdate()) {// WM_QUITメッセージが受信されたらループを終了
		//メッセージ処理
		inputManager->update();
		//ゲームの状態を更新
		game->update(inputManager);
		//ゲーム画面のレンダリング
		window->render(game);
		//更新した画面を表示
		window->show();
	}
}

void termination() {

}