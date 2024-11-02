#include "TitleScreenState.h"
#include "Game.h"
#include "InputManager.h"
#include <Windows.h>

#include "GameObject.h"
#include "PlayingState.h"




TitleScreenState::TitleScreenState() {
    //GameObjectのインスタンスを生成（筋肉実装やめたいなあ。。。。）@TODO
    appendObject("PICTURE_TITLE", L".//assets//タイトル画面2.bmp", { 1152,720 });
    appendObject("BUTTON_START", L".//assets//はじめる.bmp", { 256,128 });
    appendObject("BUTTON_STATUS", L".//assets//ステータス.bmp", { 256,128 });
    appendObject("BUTTON_GACHA", L".//assets//ガチャ.bmp", { 256,128 });
    appendObject("BUTTON_QUIT", L".//assets//おわる.bmp", { 256,128 });
    appendObject("PICTURE_KAMAYAMA", L".//assets//クマの釜山.bmp", { 172,178 });

    //各GameObjectの描画位置を設定@TODO
    gameObjects["PICTURE_TITLE"]->setObjectPosition({ 0,0 });
    gameObjects["PICTURE_KAMAYAMA"]->setObjectPosition({ 32,48 });
    gameObjects["BUTTON_START"]->setObjectPosition({ 240,352 });
    gameObjects["BUTTON_STATUS"]->setObjectPosition({ 576,352 });
    gameObjects["BUTTON_GACHA"]->setObjectPosition({ 240,528 });
    gameObjects["BUTTON_QUIT"]->setObjectPosition({ 576,528 });


    OutputDebugString(L"TitleScreenStateのインスタンスが作成されました\n");
}

TitleScreenState::~TitleScreenState()
{
}

void TitleScreenState::update(Game* game,InputManager* inputManager) {
    //タイトル画面の更新処理@TODO
    if (isClicked("BUTTON_START", inputManager)) {
        OutputDebugString(L"スタートボタンがクリックされた\n");
        game->changeState(new PlayingState());
        return;
    }
}