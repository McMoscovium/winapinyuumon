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

    //�ȉ��ABUTTON_EXIT�N���b�N����

    //�}�E�X���W���擾���A���R�̍��W��ύX
    POINT mouse = inputManager->getMousePosition();
    gameObjects[L"PICTURE_BATTER"]->setObjectPosition(mouse);

    //���R�̃X�C���O����
    const int kamayamaFrame = gameObjects.at(L"PICTURE_BATTER")->getCurrentFrameNumber();
    if (kamayamaFrame == 0) {//�X�C���O���ĂȂ�
        if (inputManager->getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_PRESSED) {
            releasedLeftButtonUntilSwingEnded = false;
            gameObjects.at(L"PICTURE_BATTER")->nextFrame();
            //OutputDebugString(L"�X�C���O�J�n\n");
        }
    }
    else if (kamayamaFrame < gameObjects.at(L"PICTURE_BATTER")->getLength()-1) {//�X�C���O�r��
        if (inputManager->getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_UP) {
            releasedLeftButtonUntilSwingEnded = true;
        }
        gameObjects.at(L"PICTURE_BATTER")->nextFrame();
    }
    else {//�X�C���O�I��
        if ((inputManager->getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_DOWN) &&
            (releasedLeftButtonUntilSwingEnded == false)) {
            //OutputDebugString(L"�X�C���O�p��\n");
        }
        else {
            releasedLeftButtonUntilSwingEnded = true;
            gameObjects.at(L"PICTURE_BATTER")->changeFrame(0);
            //OutputDebugString(L"�X�C���O�I��\n");
        }
    }
    std::wstring message = std::to_wstring(releasedLeftButtonUntilSwingEnded) + L"\n";
    OutputDebugString(message.c_str());
}
