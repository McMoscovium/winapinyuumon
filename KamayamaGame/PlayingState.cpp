#include "PlayingState.h"

#include "Game.h"
#include "GameOverState.h"



PlayingState::PlayingState()
{
}

PlayingState::~PlayingState() {}

void PlayingState::update(Game* game, InputManager* inputManager) {
    //�v���C���̍X�V����
    if (/*�v���C�I��*/false) {
        game->changeState(new GameOverState());
    }
}
