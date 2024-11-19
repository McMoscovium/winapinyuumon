#include "TitleScreenState.h"



#include "Game.h"
#include "InputManager.h"
#include <Windows.h>

#include "GameObject.h"
#include "PlayingState.h"
#include "StatusState.h"
#include "TextObject.h"
#include "TintinPitcher.h"
#include "KamayamaBatter.h"
#include "TheHundredAcreWoodStadium.h"
#include "TintinStage.h"
#include "PictureObject.h"

#include <string>


TitleScreenState::TitleScreenState(Game& game) :
    GameState(game)
{
    gameObjectManager.addFront<PictureObject>("TITLE", L".//assets//タイトル画面2.bmp", SIZE{ 1152,720 });
    gameObjectManager.addFront<PictureObject>("START", L".//assets//はじめる.bmp", SIZE{ 256,128 });
    gameObjectManager.addFront<PictureObject>("STATUS", L".//assets//ステータス.bmp", SIZE{ 256,128 });
    gameObjectManager.addFront<PictureObject>("GACHA", L".//assets//ガチャ.bmp", SIZE{ 256,128 });
    gameObjectManager.addFront<PictureObject>("QUIT", L".//assets//おわる.bmp", SIZE{ 256,128 });
    gameObjectManager.addFront<PictureObject>("KAMAYAMA", L".//assets//クマの釜山.bmp", SIZE{ 172,178 });

    showAll();

    //各GameObjectの描画位置を設定@TODO
    gameObjectManager.getObject<PictureObject>("TITLE").setObjectPosition({ 0,0 });
    gameObjectManager.getObject<PictureObject>("KAMAYAMA").setObjectPosition({ 32,48 });
    gameObjectManager.getObject<PictureObject>("START").setObjectPosition({240,352});
    gameObjectManager.getObject<PictureObject>("STATUS").setObjectPosition({ 576,352 });
    gameObjectManager.getObject<PictureObject>("GACHA").setObjectPosition({ 240,528 });
    gameObjectManager.getObject<PictureObject>("QUIT").setObjectPosition({ 576,528 });
}


void TitleScreenState::update(Game& game) {
    //タイトル画面の更新処理@TODO

    //終わるボタンクリック時@TODO

    InputManager& inputManager = game.getInputManager();

    //スタートボタンクリック時
    const PictureObject& startButton = gameObjectManager.getObject<PictureObject>("START");
    if (inputManager.isClicked(startButton)) {
        OutputDebugString(L"スタートボタンがクリックされた\n");
        Stage* tintinStage = new TintinStage();
        game.changeState(new PlayingState(game, tintinStage));
        return;
    }
    //ステータスボタンクリック時
    const PictureObject& statusButton = gameObjectManager.getObject<PictureObject>("STATUS");
    if (inputManager.isClicked(statusButton)) {
        OutputDebugString(L"ステータスボタンがクリックされた\n");
        game.changeState(new StatusState(game));
        return;
    }
}