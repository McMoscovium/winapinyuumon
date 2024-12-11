#include "GameState/GameOverState/GameOverState.h"

#include "Game/Game.h"
#include"GameState/TitleScreenState/TitleScreenState.h"
#include"Game/InputManager.h"

GameOverState::GameOverState(Game& game) :
    GameState<GameOverState,GameSubState<GameOverState>>(game)
{}

void GameOverState::update(Game& game) {
    //�Q�[���I�[�o�[�̍X�V����
    if (/*�I���{�^���������ꂽ*/true) {
        game.changeState(new TitleScreenState(game));
    }
}
