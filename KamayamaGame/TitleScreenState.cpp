#include "TitleScreenState.h"
#include "Game.h"
#include "InputManager.h"
#include <Windows.h>
#include "GameObject.h"
#include "PlayingState.h"

TitleScreenState::TitleScreenState() {
    //GameObject�̃C���X�^���X�𐶐��i�ؓ�������߂����Ȃ��B�B�B�B�j@TODO
    gameObjects.emplace(L"PICTURE_TITLE", new GameObject(L".//assets//�^�C�g�����.bmp", {1152,720}));

    //�eGameObject�̕`��ʒu��ݒ�@TODO
    gameObjects[L"PICTURE_TITLE"]->setPosition({0,0});
}

TitleScreenState::~TitleScreenState()
{
}

void TitleScreenState::update(Game* game,InputManager* inputManager) {
    //�^�C�g����ʂ̍X�V����
    if (/*�X�^�[�g�{�^���������ꂽ*/false) {
        game->changeState(new PlayingState());
    }
}

const std::unordered_map<std::wstring, GameObject*>* TitleScreenState::getGameObjects()const
{
    return &gameObjects;
}