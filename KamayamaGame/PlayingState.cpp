#include "PlayingState.h"

#include "Game.h"
#include "GameOverState.h"
#include "InputManager.h"

#include"TitleScreenState.h"



PlayingState::PlayingState()
{
    //GameObjectのインスタンスを生成
    appendObject(L"PICTURE_FIELD", L".//assets//フィールド.bmp", { 1152,720 });
    appendObject(L"PICTURE_BATTER", L".//assets//打者.bmp", { 360,391 });
    appendObject(L"BUTTON_EXIT", L".//assets//おわる.bmp", { 256,128 });

    //各GameObjectの描画位置を設定
    gameObjects.at(L"PICTURE_FIELD")->setObjectPosition({ 0,0 });
    gameObjects.at(L"PICTURE_BATTER")->setObjectPosition({ 32,48 });
    gameObjects.at(L"BUTTON_EXIT")->setObjectPosition({ 850,500 });
    
    OutputDebugString(L"PlayingStateのインスタンスが作成されました\n");
}


void PlayingState::update(Game* game, InputManager* inputManager) {
    //プレイ中の更新処理



    if (isClicked(L"BUTTON_EXIT", inputManager)) {
        game->changeState(new TitleScreenState());
        return;
    }

    //以下、プレイ続行
    POINT mouse = inputManager->getMousePosition();
    gameObjects[L"PICTURE_BATTER"]->setObjectPosition(mouse);
}
