#include "GameOverState.h"

#include "Game.h"
#include"TitleScreenState.h"
#include"InputManager.h"

void GameOverState::update(Game* game,InputManager* inputManager) {
    //�Q�[���I�[�o�[�̍X�V����
    if (/*�I���{�^���������ꂽ*/true) {
        game->changeState(new TitleScreenState());
    }
}

const std::unordered_map<std::wstring, GameObject*>* GameOverState::getGameObjects() const
{
    return nullptr;
}