#include "TitleScreenState.h"
#include "Game.h"
#include "InputManager.h"
#include <Windows.h>
#include "GameObject.h"
#include "PlayingState.h"

TitleScreenState::TitleScreenState() {
    //GameObject�̃C���X�^���X�𐶐��i�ؓ�������߂����Ȃ��B�B�B�B�j@TODO
    gameObjects.emplace(TitleScreenState::ObjectName::PICTURE_TITLE, new GameObject(L".//assets//�^�C�g�����.bmp", { 1152,720 }));

    //�eGameObject�̕`��ʒu��ݒ�@TODO
    gameObjects[TitleScreenState::ObjectName::PICTURE_TITLE]->setPosition({ 0,0 });
}

void TitleScreenState::update(Game* game,InputManager* inputManager) {
    //�^�C�g����ʂ̍X�V����
    if (/*�X�^�[�g�{�^���������ꂽ*/false) {
        game->changeState(new PlayingState());
    }
}