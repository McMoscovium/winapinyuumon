#include<Windows.h>
#include"Window.h"
#include"Game.h"
#include "InputManager.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInst,
	LPSTR lpszCmdLine,
	int nShowCmd) {

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
		game.update();
		//更新した画面を表示
		window.show();
	}
	return 0;
}