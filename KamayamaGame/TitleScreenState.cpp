#include "TitleScreenState.h"

#include "Game.h"
#include "InputManager.h"
#include <Windows.h>

#include "GameObject.h"
#include "PlayingState.h"
#include "StatusState.h"
#include "TextObject.h"
#include "TintinPitcher.h"
#include "KamayamaBatter.h"
#include "TheHundredAcreWoodStadium.h"




TitleScreenState::TitleScreenState(Game& game) :
    GameState(game)

{
    //GameObject�̃C���X�^���X�𐶐��i�ؓ�������߂����Ȃ��B�B�B�B�j@TODO
    appendObject(L"PICTURE_TITLE", L".//assets//�^�C�g�����2.bmp", { 1152,720 });
    

    appendObject(L"BUTTON_START", L".//assets//�͂��߂�.bmp", { 256,128 });
    appendObject(L"BUTTON_STATUS", L".//assets//�X�e�[�^�X.bmp", { 256,128 });
    appendObject(L"BUTTON_GACHA", L".//assets//�K�`��.bmp", { 256,128 });
    appendObject(L"BUTTON_QUIT", L".//assets//�����.bmp", { 256,128 });
    appendObject(L"PICTURE_KAMAYAMA", L".//assets//�N�}�̊��R.bmp", { 172,178 });

    showAll();

    //�eGameObject�̕`��ʒu��ݒ�@TODO
    getGameObject(L"PICTURE_TITLE").setObjectPosition({ 0,0 });
    getGameObject(L"PICTURE_KAMAYAMA").setObjectPosition({ 32,48 });
    getGameObject(L"BUTTON_START").setObjectPosition({ 240,352 });
    getGameObject(L"BUTTON_STATUS").setObjectPosition({ 576,352 });
    getGameObject(L"BUTTON_GACHA").setObjectPosition({ 240,528 });
    getGameObject(L"BUTTON_QUIT").setObjectPosition({ 576,528 });

    gameObjects.emplace(L"TEXT_TEST", new TextObject(L"TEXT_TEST", L"aiueo"));
    objectOrder.push_back(L"TEXT_TEST");

    getGameObject(L"TEXT_TEST").appear();

    OutputDebugString(L"TitleScreenState�̃C���X�^���X���쐬����܂���\n");
}


void TitleScreenState::update(Game& game) {
    //�^�C�g����ʂ̍X�V����@TODO

    //�I���{�^���N���b�N��@TODO

    InputManager& inputManager = game.getInputManager();

    //�X�^�[�g�{�^���N���b�N��
    GameObject startButton = getGameObject(L"BUTTON_START");
    if (inputManager.isClicked(startButton)) {
        OutputDebugString(L"�X�^�[�g�{�^�����N���b�N���ꂽ\n");
        game.changeState(new PlayingState(game, new KamayamaBatter, new TintinPitcher, new TheHundredAcreWoodStadium()));
        return;
    }
    GameObject statusButton = getGameObject(L"BUTTON_STATUS");
    //�X�e�[�^�X�{�^���N���b�N��
    if (inputManager.isClicked(statusButton)) {
        OutputDebugString(L"�X�e�[�^�X�{�^�����N���b�N���ꂽ\n");
        game.changeState(new StatusState(game));
        return;
    }
}