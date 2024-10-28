#include<Windows.h>
#include"Window.h"
#include"Game.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInst,
	LPSTR lpszCmdLine,
	int nShowCmd) {

	Window window(hInstance, nShowCmd);//Windowクラスのインスタンスを作成

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
		/*
		ゲームの処理をここに追加
		*/
	}
	return 0;
}