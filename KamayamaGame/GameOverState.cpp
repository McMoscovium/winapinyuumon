#include "GameOverState.h"

#include "Game.h"
#include"TitleScreenState.h"

void GameOverState::update(Game* game) {
    //�Q�[���I�[�o�[�̍X�V����
    if (/*�I���{�^���������ꂽ*/true) {
        game->changeState(new TitleScreenState());
    }
}