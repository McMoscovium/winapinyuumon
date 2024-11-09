#include "PlayingState.h"

#include "Game.h"
#include "GameOverState.h"
#include "InputManager.h"
#include "GameSubState.h"

#include <algorithm>
#include <memory>

#include"TitleScreenState.h"
#include "WaitingPitchingSubState.h"


using namespace std;




PlayingState::PlayingState(Game& game):
    GameState(game)
{

    //GameObject�̃C���X�^���X�𐶐�
    appendObjectFromFile(L"PICTURE_FIELD", L".//assets//�t�B�[���h.bmp", { 1152,720 });

    BatBoundingBox box = BatBoundingBox(L".//assets//battingJudgeFrame.bmp", L"BOX_BAT", { 50,50 }, { 0,0 });
    appendObject(L"BOX_BAT", box);

    Batter batter = Batter(L".//assets//�Ŏ�.bmp", L"PICTURE_BATTER", { 360,391 }, *this);
    appendObject(L"PICTURE_BATTER", batter);

    appendObjectFromFile(L"BUTTON_EXIT", L".//assets//�����.bmp", { 256,128 });
    appendObjectFromFile(L"PICTURE_PITCHER", L".//assets//����.bmp", { 112,182 });
    appendObjectFromFile(L"PICTURE_BALL", L".//assets//�{�[��.bmp", { 41,50 });
    

    getBoundingBox().setPosition({ 0,0 });
    getBoundingBox().hide();

    //�eGameObject�̕`��ʒu��ݒ�
    gameObjects.at(L"PICTURE_FIELD").setPosition({ 0,0 });
    gameObjects.at(L"PICTURE_BATTER").setPosition({ 400,400 });
    gameObjects.at(L"BUTTON_EXIT").setPosition({ 850,500 });
    gameObjects.at(L"PICTURE_PITCHER").setPosition({ 514, 22 });
    
    changeSubState(make_unique<WaitingPitchingSubState>(*this));

    OutputDebugString(L"PlayingState�̃C���X�^���X���쐬����܂���\n");
}

void PlayingState::update() {
    GameObject& batter = getBatter();
    POINT pos = batter.getPosition();
    std::wstring message = L"�o�b�^�[���W: ( " + std::to_wstring(pos.x) + L", " + std::to_wstring(pos.y) + L" )\n";
    OutputDebugString(message.c_str());
    currentSubState->update();
}


void PlayingState::updateBatterAnimation(const InputManager& inputManager)
{
    //���R�̃X�C���O����
    const int kamayamaFrame = gameObjects.at(L"PICTURE_BATTER").getCurrentFrameNumber();
    if (kamayamaFrame == 0) {//�X�C���O���ĂȂ�
        if (inputManager.getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_PRESSED) {
            releasedLeftButtonUntilSwingEnded = false;
            gameObjects.at(L"PICTURE_BATTER").nextFrame();
            //OutputDebugString(L"�X�C���O�J�n\n");
        }
    }
    else if (kamayamaFrame < gameObjects.at(L"PICTURE_BATTER").getLength() - 1) {//�X�C���O�r��
        if (inputManager.getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_UP) {
            releasedLeftButtonUntilSwingEnded = true;
        }
        gameObjects.at(L"PICTURE_BATTER").nextFrame();
    }
    else {//�X�C���O�I��
        if ((inputManager.getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_DOWN) &&
            (releasedLeftButtonUntilSwingEnded == false)) {
            //OutputDebugString(L"�X�C���O�p��\n");
        }
        else {
            releasedLeftButtonUntilSwingEnded = true;
            gameObjects.at(L"PICTURE_BATTER").changeFrame(0);
            //OutputDebugString(L"�X�C���O�I��\n");
        }
    }
}

Batter& PlayingState::getBatter() {
    return static_cast<Batter&>(getGameObject(L"PICTURE_BATTER"));
}

BatBoundingBox& PlayingState::getBoundingBox()
{
    return static_cast<BatBoundingBox&>(getGameObject(L"BOX_BAT"));
}
