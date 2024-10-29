#include "GameOverState.h"

#include "Game.h"
#include"TitleScreenState.h"
#include"InputManager.h"

void GameOverState::update(Game* game,InputManager* inputManager) {
    //ゲームオーバーの更新処理
    if (/*終了ボタンが押された*/true) {
        game->changeState(new TitleScreenState());
    }
}