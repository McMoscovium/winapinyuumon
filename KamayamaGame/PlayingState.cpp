#include "PlayingState.h"

#include "Game.h"
#include "GameOverState.h"
#include "InputManager.h"

#include"TitleScreenState.h"



PlayingState::PlayingState()
{
    //GameObject�̃C���X�^���X�𐶐�
    appendObject(L"PICTURE_FIELD", L".//assets//�t�B�[���h.bmp", { 1152,720 });
    appendObject(L"PICTURE_BATTER", L".//assets//�Ŏ�.bmp", { 360,391 });
    appendObject(L"BUTTON_EXIT", L".//assets//�����.bmp", { 256,128 });

    //�eGameObject�̕`��ʒu��ݒ�
    gameObjects.at(L"PICTURE_FIELD")->setObjectPosition({ 0,0 });
    gameObjects.at(L"PICTURE_BATTER")->setObjectPosition({ 32,48 });
    gameObjects.at(L"BUTTON_EXIT")->setObjectPosition({ 850,500 });
    
    OutputDebugString(L"PlayingState�̃C���X�^���X���쐬����܂���\n");
}


void PlayingState::update(Game* game, InputManager* inputManager) {
    //�v���C���̍X�V����



    if (isClicked(L"BUTTON_EXIT", inputManager)) {
        game->changeState(new TitleScreenState());
        return;
    }

    //�ȉ��A�v���C���s
    POINT mouse = inputManager->getMousePosition();
    gameObjects[L"PICTURE_BATTER"]->setObjectPosition(mouse);
}
