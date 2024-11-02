#include "PlayingState.h"

#include "Game.h"
#include "GameOverState.h"
#include "InputManager.h"



PlayingState::PlayingState()
{
    //GameObjectのインスタンスを生成
    appendObject("PICTURE_FIELD", L".//assets//フィールド.bmp", { 1152,720 });
    appendObject("PICTURE_BATTER", L".//assets//打者.bmp", { 360,391 });

    //各GameObjectの描画位置を設定
    gameObjects["PICTURE_FIELD"]->setObjectPosition({ 0,0 });
    gameObjects["PICTURE_BATTER"]->setObjectPosition({ 32,48 });
    
    OutputDebugString(L"PlayingStateのインスタンスが作成されました\n");
}

PlayingState::~PlayingState() {}

void PlayingState::update(Game* game, InputManager* inputManager) {
    //プレイ中の更新処理
    if (/*プレイ終了*/false) {
        game->changeState(new GameOverState());
    }
    //以下、プレイ続行
    POINT mouse = inputManager->getMousePosition();
    gameObjects["PICTURE_BATTER"]->setObjectPosition(mouse);
}
