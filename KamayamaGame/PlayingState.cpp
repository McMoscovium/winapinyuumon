#include "PlayingState.h"

#include "Game.h"
#include "GameOverState.h"

void PlayingState::update(Game* game) {
    //プレイ中の更新処理
    if (/*プレイ終了*/true) {
        game->changeState(new GameOverState());
    }
}

PlayingState::~PlayingState() {}

