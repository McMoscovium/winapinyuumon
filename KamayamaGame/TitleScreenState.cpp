#include "TitleScreenState.h"

#include "Game.h"

void TitleScreenState::update(Game* game) {
    //�^�C�g����ʂ̍X�V����
    if (/*�X�^�[�g�{�^���������ꂽ*/true) {
        game->changeState(new PlayingState());
    }
}