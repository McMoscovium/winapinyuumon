#include "TitleScreenState.h"
#include "Game.h"
#include "InputManager.h"
#include <Windows.h>

#include "GameObject.h"
#include "PlayingState.h"




TitleScreenState::TitleScreenState() {
    //GameObject�̃C���X�^���X�𐶐��i�ؓ�������߂����Ȃ��B�B�B�B�j@TODO
    appendObject("PICTURE_TITLE", L".//assets//�^�C�g�����2.bmp", { 1152,720 });
    appendObject("BUTTON_START", L".//assets//�͂��߂�.bmp", { 256,128 });
    appendObject("BUTTON_STATUS", L".//assets//�X�e�[�^�X.bmp", { 256,128 });
    appendObject("BUTTON_GACHA", L".//assets//�K�`��.bmp", { 256,128 });
    appendObject("BUTTON_QUIT", L".//assets//�����.bmp", { 256,128 });
    appendObject("PICTURE_KAMAYAMA", L".//assets//�N�}�̊��R.bmp", { 172,178 });

    //�eGameObject�̕`��ʒu��ݒ�@TODO
    gameObjects["PICTURE_TITLE"]->setObjectPosition({ 0,0 });
    gameObjects["PICTURE_KAMAYAMA"]->setObjectPosition({ 32,48 });
    gameObjects["BUTTON_START"]->setObjectPosition({ 240,352 });
    gameObjects["BUTTON_STATUS"]->setObjectPosition({ 576,352 });
    gameObjects["BUTTON_GACHA"]->setObjectPosition({ 240,528 });
    gameObjects["BUTTON_QUIT"]->setObjectPosition({ 576,528 });


    OutputDebugString(L"TitleScreenState�̃C���X�^���X���쐬����܂���\n");
}

TitleScreenState::~TitleScreenState()
{
}

void TitleScreenState::update(Game* game,InputManager* inputManager) {
    //�^�C�g����ʂ̍X�V����@TODO
    if (isClicked("BUTTON_START", inputManager)) {
        OutputDebugString(L"�X�^�[�g�{�^�����N���b�N���ꂽ\n");
        game->changeState(new PlayingState());
        return;
    }
}