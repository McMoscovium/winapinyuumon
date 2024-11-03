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

    //以下、BUTTON_EXITクリック無し

    //マウス座標を取得し、釜山の座標を変更
    POINT mouse = inputManager->getMousePosition();
    gameObjects[L"PICTURE_BATTER"]->setObjectPosition(mouse);

    //釜山のスイング処理
    const int kamayamaFrame = gameObjects.at(L"PICTURE_BATTER")->getCurrentFrameNumber();
    if (kamayamaFrame == 0) {//スイングしてない
        if (inputManager->getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_PRESSED) {
            releasedLeftButtonUntilSwingEnded = false;
            gameObjects.at(L"PICTURE_BATTER")->nextFrame();
            //OutputDebugString(L"スイング開始\n");
        }
    }
    else if (kamayamaFrame < gameObjects.at(L"PICTURE_BATTER")->getLength()-1) {//スイング途中
        if (inputManager->getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_UP) {
            releasedLeftButtonUntilSwingEnded = true;
        }
        gameObjects.at(L"PICTURE_BATTER")->nextFrame();
    }
    else {//スイング終了
        if ((inputManager->getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_DOWN) &&
            (releasedLeftButtonUntilSwingEnded == false)) {
            //OutputDebugString(L"スイング継続\n");
        }
        else {
            releasedLeftButtonUntilSwingEnded = true;
            gameObjects.at(L"PICTURE_BATTER")->changeFrame(0);
            //OutputDebugString(L"スイング終了\n");
        }
    }
    std::wstring message = std::to_wstring(releasedLeftButtonUntilSwingEnded) + L"\n";
    OutputDebugString(message.c_str());
}
