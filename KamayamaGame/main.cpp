#include <Windows.h>
#include "Window.h"
#include "Game.h"
#include "InputManager.h"

//開発用
#include <iostream>

const LPCWSTR gameName = L"クマの釜山のホームランダービー！";




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


	//必要なインスタンスを作成、初期化
	Window window(hInstance, nShowCmd);
	Game game(&window);
	InputManager inputManager;

	//メインループ
	MSG msg = {};
	while (true) {
		//メッセージ処理
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			//終了メッセージの場合
			if (msg.message == WM_QUIT) {
				return 0;//アプリを終了
			}
		}
		//終了メッセージでない場合
		//入力の更新
		inputManager.update();
		//ゲームの状態を更新
		game.update(&inputManager);
		//更新した画面を表示
		window.show();
	}


	// コンソールが自動で閉じないようにする
	std::cout << "Press Enter to exit...";
	std::cin.get();

	// コンソールを解放
	FreeConsole();

	return 0;
}