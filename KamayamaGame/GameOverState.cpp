#include "GameOverState.h"

#include "Game.h"
#include"TitleScreenState.h"
#include"InputManager.h"

#include <memory>

using namespace std;

GameOverState::GameOverState(Game& game) :GameState<GameOverState>(game)
{}

GameOverState::~GameOverState()
{
}

void GameOverState::update() {
    //ゲームオーバーの更新処理
    if (/*終了ボタンが押された*/true) {
        game.changeState(make_unique<TitleScreenState>(game));
    }
}
