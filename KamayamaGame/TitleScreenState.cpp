#include "TitleScreenState.h"

#include "Game.h"
#include "InputManager.h"
#include <Windows.h>

#include "IGameState.h"
#include "GameObject.h"
#include "PlayingState.h"
#include "StatusState.h"
#include <memory>

using namespace std;


TitleScreenState::TitleScreenState(Game& game) :GameState<TitleScreenState>(game)
{
    //GameObject�̃C���X�^���X�𐶐��i�ؓ�������߂����Ȃ��B�B�B�B�j@TODO
    appendObjectFromFile(L"PICTURE_TITLE", L".//assets//�^�C�g�����2.bmp", { 1152,720 });
    appendObjectFromFile(L"BUTTON_START", L".//assets//�͂��߂�.bmp", { 256,128 });
    appendObjectFromFile(L"BUTTON_STATUS", L".//assets//�X�e�[�^�X.bmp", { 256,128 });
    appendObjectFromFile(L"BUTTON_GACHA", L".//assets//�K�`��.bmp", { 256,128 });
    appendObjectFromFile(L"BUTTON_QUIT", L".//assets//�����.bmp", { 256,128 });
    appendObjectFromFile(L"PICTURE_KAMAYAMA", L".//assets//�N�}�̊��R.bmp", { 172,178 });

    //�eGameObject�̕`��ʒu��ݒ�@TODO
    gameObjects.at(L"PICTURE_TITLE").setPosition({ 0,0 });
    gameObjects.at(L"PICTURE_KAMAYAMA").setPosition({ 32,48 });
    gameObjects.at(L"BUTTON_START").setPosition({ 240,352 });
    gameObjects.at(L"BUTTON_STATUS").setPosition({ 576,352 });
    gameObjects.at(L"BUTTON_GACHA").setPosition({ 240,528 });
    gameObjects.at(L"BUTTON_QUIT").setPosition({ 576,528 });



    OutputDebugString(L"TitleScreenState�̃C���X�^���X���쐬����܂���\n");
}


void TitleScreenState::update() {
    const InputManager& inputManager = game.getInputManager();
    //�^�C�g����ʂ̍X�V����@TODO

    //�I���{�^���N���b�N��@TODO
    
    //�X�^�[�g�{�^���N���b�N��
    const GameObject& startButton = getGameObject(L"BUTTON_START");
    if (inputManager.isClicked(startButton)) {
        OutputDebugString(L"�X�^�[�g�{�^�����N���b�N���ꂽ\n");
        game.changeState(make_unique<PlayingState>(game));
        return;
    }

    //�X�e�[�^�X�{�^���N���b�N��
    const GameObject& statusButton = getGameObject(L"BUTTON_STATUS");
    if (inputManager.isClicked(statusButton)) {
        OutputDebugString(L"�X�e�[�^�X�{�^�����N���b�N���ꂽ\n");
        game.changeState(make_unique<StatusState>(game));
        return;
    }
}