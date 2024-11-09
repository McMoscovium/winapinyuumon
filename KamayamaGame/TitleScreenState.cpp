#include "TitleScreenState.h"

#include "Game.h"
#include "InputManager.h"
#include <Windows.h>

#include "IGameState.h"
#include "GameObject.h"
#include "PlayingState.h"
#include "StatusState.h"
#include <memory>

using namespace std;


TitleScreenState::TitleScreenState(Game& game) :GameState<TitleScreenState>(game)
{
    //GameObjectのインスタンスを生成（筋肉実装やめたいなあ。。。。）@TODO
    appendObjectFromFile(L"PICTURE_TITLE", L".//assets//タイトル画面2.bmp", { 1152,720 });
    appendObjectFromFile(L"BUTTON_START", L".//assets//はじめる.bmp", { 256,128 });
    appendObjectFromFile(L"BUTTON_STATUS", L".//assets//ステータス.bmp", { 256,128 });
    appendObjectFromFile(L"BUTTON_GACHA", L".//assets//ガチャ.bmp", { 256,128 });
    appendObjectFromFile(L"BUTTON_QUIT", L".//assets//おわる.bmp", { 256,128 });
    appendObjectFromFile(L"PICTURE_KAMAYAMA", L".//assets//クマの釜山.bmp", { 172,178 });

    //各GameObjectの描画位置を設定@TODO
    gameObjects.at(L"PICTURE_TITLE").setPosition({ 0,0 });
    gameObjects.at(L"PICTURE_KAMAYAMA").setPosition({ 32,48 });
    gameObjects.at(L"BUTTON_START").setPosition({ 240,352 });
    gameObjects.at(L"BUTTON_STATUS").setPosition({ 576,352 });
    gameObjects.at(L"BUTTON_GACHA").setPosition({ 240,528 });
    gameObjects.at(L"BUTTON_QUIT").setPosition({ 576,528 });



    OutputDebugString(L"TitleScreenStateのインスタンスが作成されました\n");
}


void TitleScreenState::update() {
    const InputManager& inputManager = game.getInputManager();
    //タイトル画面の更新処理@TODO

    //終わるボタンクリック時@TODO
    
    //スタートボタンクリック時
    const GameObject& startButton = getGameObject(L"BUTTON_START");
    if (inputManager.isClicked(startButton)) {
        OutputDebugString(L"スタートボタンがクリックされた\n");
        game.changeState(make_unique<PlayingState>(game));
        return;
    }

    //ステータスボタンクリック時
    const GameObject& statusButton = getGameObject(L"BUTTON_STATUS");
    if (inputManager.isClicked(statusButton)) {
        OutputDebugString(L"ステータスボタンがクリックされた\n");
        game.changeState(make_unique<StatusState>(game));
        return;
    }
}