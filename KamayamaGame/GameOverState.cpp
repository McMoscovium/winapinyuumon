#include "GameOverState.h"

#include "Game.h"
#include"TitleScreenState.h"
#include"InputManager.h"

GameOverState::GameOverState()
{}

GameOverState::~GameOverState()
{
}

void GameOverState::update(Game* game,InputManager* inputManager) {
    //ゲームオーバーの更新処理
    if (/*終了ボタンが押された*/true) {
        game->changeState(new TitleScreenState());
    }
}
