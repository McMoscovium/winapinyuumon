#include "TitleScreenState.h"
#include "Game.h"
#include "InputManager.h"
#include <Windows.h>

#include "GameObject.h"
#include "PlayingState.h"

//�J���p
#include <iostream>
TitleScreenState::TitleScreenState() {
    //GameObject�̃C���X�^���X�𐶐��i�ؓ�������߂����Ȃ��B�B�B�B�j@TODO
    appendObject("PICTURE_TITLE", L".//assets//�^�C�g�����2.bmp", { 1152,720 });

    //�eGameObject�̕`��ʒu��ݒ�@TODO
    gameObjects["PICTURE_TITLE"]->setObjectPosition({ 0,0 });

    std::cout << "TitleScreenState�̃C���X�^���X���쐬����܂���" << std::endl;
}

TitleScreenState::~TitleScreenState()
{
}

void TitleScreenState::update(Game* game,InputManager* inputManager) {
    //�^�C�g����ʂ̍X�V����@TODO
    if (/*�X�^�[�g�{�^���������ꂽ*/false) {
        game->changeState(new PlayingState());
    }
}
