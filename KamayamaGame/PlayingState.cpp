#include "PlayingState.h"

#include "Game.h"
#include "GameOverState.h"
#include "InputManager.h"



PlayingState::PlayingState()
{
    //GameObject�̃C���X�^���X�𐶐�
    appendObject("PICTURE_FIELD", L".//assets//�t�B�[���h.bmp", { 1152,720 });
    appendObject("PICTURE_BATTER", L".//assets//�Ŏ�.bmp", { 360,391 });

    //�eGameObject�̕`��ʒu��ݒ�
    gameObjects["PICTURE_FIELD"]->setObjectPosition({ 0,0 });
    gameObjects["PICTURE_BATTER"]->setObjectPosition({ 32,48 });
    
    OutputDebugString(L"PlayingState�̃C���X�^���X���쐬����܂���\n");
}

PlayingState::~PlayingState() {}

void PlayingState::update(Game* game, InputManager* inputManager) {
    //�v���C���̍X�V����
    if (/*�v���C�I��*/false) {
        game->changeState(new GameOverState());
    }
    //�ȉ��A�v���C���s
    POINT mouse = inputManager->getMousePosition();
    gameObjects["PICTURE_BATTER"]->setObjectPosition(mouse);
}
