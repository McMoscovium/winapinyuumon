#include "PlayingState.h"

#include "Game.h"
#include "GameOverState.h"

void PlayingState::update(Game* game, InputManager* inputManager) {
    //�v���C���̍X�V����
    if (/*�v���C�I��*/true) {
        game->changeState(new GameOverState());
    }
}

PlayingState::~PlayingState() {}

