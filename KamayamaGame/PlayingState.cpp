#include "PlayingState.h"

#include "Game.h"
#include "GameOverState.h"

void PlayingState::update(Game* game, InputManager* inputManager) {
    //プレイ中の更新処理
    if (/*プレイ終了*/true) {
        game->changeState(new GameOverState());
    }
}

const std::unordered_map<std::wstring, GameObject*>* PlayingState::getGameObjects() const
{
    return nullptr;
}

PlayingState::~PlayingState() {}

