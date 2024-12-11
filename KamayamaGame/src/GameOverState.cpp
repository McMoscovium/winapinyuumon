#include "GameState/GameOverState/GameOverState.h"

#include "Game/Game.h"
#include"GameState/TitleScreenState/TitleScreenState.h"
#include"Game/InputManager.h"

GameOverState::GameOverState(Game& game) :
    GameState<GameOverState,GameSubState<GameOverState>>(game)
{}

void GameOverState::update(Game& game) {
    //ゲームオーバーの更新処理
    if (/*終了ボタンが押された*/true) {
        game.changeState(new TitleScreenState(game));
    }
}
