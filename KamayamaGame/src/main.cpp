#include <Windows.h>
#include "Game/Window.h"
#include "Game/Game.h"
#include "Game/InputManager.h"
#include "GameState/TitleScreenState/TitleScreenState.h"


//開発用
#include <iostream>

const LPCWSTR gameName = L"クマの釜山のホームランダービー！";


void mainLoop(Game* game,Window* window);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInst,
	LPSTR lpszCmdLine,
	int nShowCmd) {

	//初期化パート
	
	//必要なインスタンスを作成、初期化

	InputManager inputManager;
	
	Game game = Game(inputManager, hInstance);

	//ウィンドウ関係
	Window window(hInstance, nShowCmd, &inputManager, game);
	//
	game.registerWindow(&window);
	game.changeState(new TitleScreenState(game));
	//初期画面レンダリング
	window.render(game.getCurrentState()->getGameObjectManager());
	//初期画面表示
	window.show();
	mainLoop(&game, &window);

	//終了処理
	//WM_QUITメッセージがもう出されているので、はやく終わる。
	window.termination();

	return 0;
}

void mainLoop(Game* game,Window* window) {
	LARGE_INTEGER frequency, start, end;//タイマー関係
	double elapsed;
	QueryPerformanceFrequency(&frequency);//周波数
	QueryPerformanceCounter(&start);//開始時カウント

	while (window->update(game)) {// WM_QUITメッセージが受信されたらループを終了
		//ウィンドウプロシージャ終了時カウント
		QueryPerformanceCounter(&end);
		//経過時間
		elapsed = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
		//1フレーム分の時間がたつまで待つ
		if (elapsed > 1.0 / window->getFps()) {
			//1フレームの時間が経過
			//60秒に1回呼び出す
			//ゲームロジックをアップデート
			game->getInputManager().update();
			game->update();
			//再描画要求
			InvalidateRect(window->getHandle(), NULL, FALSE);
			QueryPerformanceCounter(&start); // 次のフレームの基準時間を設定
		}
	}
	//WM_QUITを受け取るとループを抜ける
}