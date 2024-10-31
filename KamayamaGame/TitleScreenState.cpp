#include "TitleScreenState.h"
#include "Game.h"
#include "InputManager.h"
#include <Windows.h>

#include "GameObject.h"
#include "PlayingState.h"

//開発用
#include <iostream>
TitleScreenState::TitleScreenState() {
    //GameObjectのインスタンスを生成（筋肉実装やめたいなあ。。。。）@TODO
    appendObject("PICTURE_TITLE", L".//assets//タイトル画面2.bmp", { 1152,720 });

    //各GameObjectの描画位置を設定@TODO
    gameObjects["PICTURE_TITLE"]->setObjectPosition({ 0,0 });

    std::cout << "TitleScreenStateのインスタンスが作成されました" << std::endl;
}

TitleScreenState::~TitleScreenState()
{
}

void TitleScreenState::update(Game* game,InputManager* inputManager) {
    //タイトル画面の更新処理@TODO
    if (/*スタートボタンが押された*/false) {
        game->changeState(new PlayingState());
    }
}
