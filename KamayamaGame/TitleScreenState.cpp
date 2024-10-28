#include "TitleScreenState.h"

#include "Game.h"

void TitleScreenState::update(Game* game) {
    //タイトル画面の更新処理
    if (/*スタートボタンが押された*/true) {
        game->changeState(new PlayingState());
    }
}