#include "GameOverState.h"

#include "Game.h"
#include"TitleScreenState.h"

void GameOverState::update(Game* game) {
    //ゲームオーバーの更新処理
    if (/*終了ボタンが押された*/true) {
        game->changeState(new TitleScreenState());
    }
}