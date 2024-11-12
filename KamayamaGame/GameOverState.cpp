#include "GameOverState.h"

#include "Game.h"
#include"TitleScreenState.h"
#include"InputManager.h"

GameOverState::GameOverState(Game& game) :
    GameState<GameOverState,GameSubState<GameOverState>>(game)
{}

void GameOverState::update(Game& game) {
    //�Q�[���I�[�o�[�̍X�V����
    if (/*�I���{�^���������ꂽ*/true) {
        game.changeState(new TitleScreenState(game));
    }
}
