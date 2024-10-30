#include "TitleScreenState.h"
#include "Game.h"
#include "InputManager.h"
#include <Windows.h>
#include "GameObject.h"
#include "PlayingState.h"

TitleScreenState::TitleScreenState() {
    //GameObjectのインスタンスを生成（筋肉実装やめたいなあ。。。。）@TODO
    gameObjects.emplace(TitleScreenState::ObjectName::PICTURE_TITLE, new GameObject(L".//assets//タイトル画面.bmp", { 1152,720 }));

    //各GameObjectの描画位置を設定@TODO
    gameObjects[TitleScreenState::ObjectName::PICTURE_TITLE]->setPosition({ 0,0 });
}

void TitleScreenState::update(Game* game,InputManager* inputManager) {
    //タイトル画面の更新処理
    if (/*スタートボタンが押された*/false) {
        game->changeState(new PlayingState());
    }
}