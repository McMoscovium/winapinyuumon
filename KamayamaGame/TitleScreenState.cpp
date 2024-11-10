#include "TitleScreenState.h"

#include "Game.h"
#include "InputManager.h"
#include <Windows.h>

#include "GameObject.h"
#include "PlayingState.h"
#include "StatusState.h"




TitleScreenState::TitleScreenState(Game& game) :
    GameState(game)

{
    //GameObjectのインスタンスを生成（筋肉実装やめたいなあ。。。。）@TODO
    appendObject(L"PICTURE_TITLE", L".//assets//タイトル画面2.bmp", { 1152,720 });
    appendObject(L"BUTTON_START", L".//assets//はじめる.bmp", { 256,128 });
    appendObject(L"BUTTON_STATUS", L".//assets//ステータス.bmp", { 256,128 });
    appendObject(L"BUTTON_GACHA", L".//assets//ガチャ.bmp", { 256,128 });
    appendObject(L"BUTTON_QUIT", L".//assets//おわる.bmp", { 256,128 });
    appendObject(L"PICTURE_KAMAYAMA", L".//assets//クマの釜山.bmp", { 172,178 });

    //各GameObjectの描画位置を設定@TODO
    gameObjects.at(L"PICTURE_TITLE").setObjectPosition({ 0,0 });
    gameObjects.at(L"PICTURE_KAMAYAMA").setObjectPosition({ 32,48 });
    gameObjects.at(L"BUTTON_START").setObjectPosition({ 240,352 });
    gameObjects.at(L"BUTTON_STATUS").setObjectPosition({ 576,352 });
    gameObjects.at(L"BUTTON_GACHA").setObjectPosition({ 240,528 });
    gameObjects.at(L"BUTTON_QUIT").setObjectPosition({ 576,528 });


    OutputDebugString(L"TitleScreenStateのインスタンスが作成されました\n");
}


void TitleScreenState::update(Game& game) {
    //タイトル画面の更新処理@TODO

    //終わるボタンクリック時@TODO

    InputManager& inputManager = game.getInputManager();

    //スタートボタンクリック時
    GameObject startButton = getGameObject(L"BUTTON_START");
    if (inputManager.isClicked(startButton)) {
        OutputDebugString(L"スタートボタンがクリックされた\n");
        game.changeState(new PlayingState(game));
        return;
    }
    GameObject statusButton = getGameObject(L"BUTTON_STATUS");
    //ステータスボタンクリック時
    if (inputManager.isClicked(statusButton)) {
        OutputDebugString(L"ステータスボタンがクリックされた\n");
        game.changeState(new StatusState(game));
        return;
    }
}