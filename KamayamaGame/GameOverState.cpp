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
    //�Q�[���I�[�o�[�̍X�V����
    if (/*�I���{�^���������ꂽ*/true) {
        game.changeState(make_unique<TitleScreenState>(game));
    }
}
