#include "PlayingState.h"

#include "Game.h"
#include "GameOverState.h"



PlayingState::PlayingState()
{
}

PlayingState::~PlayingState() {}

void PlayingState::update(Game* game, InputManager* inputManager) {
    //プレイ中の更新処理
    if (/*プレイ終了*/false) {
        game->changeState(new GameOverState());
    }
}
