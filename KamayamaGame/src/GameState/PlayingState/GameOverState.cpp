#include "GameState/GameOverState/GameOverState.h"

#include "Game/Game.h"
#include"GameState/TitleScreenState/TitleScreenState.h"
#include"Game/InputManager.h"

GameOverState::GameOverState(Game& game, AudioManager& audioManager) :
    GameState<GameOverState,GameSubState<GameOverState>>(game, audioManager)
{}

void GameOverState::update(Game& game) {
    //�Q�[���I�[�o�[�̍X�V����
    if (/*�I���{�^���������ꂽ*/true) {
        game.changeState(new TitleScreenState(game, audioManager));
    }
}
