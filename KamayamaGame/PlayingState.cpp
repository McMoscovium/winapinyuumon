#include "PlayingState.h"

#include "Game.h"
#include "GameSubState.h"
#include "GameOverState.h"
#include "InputManager.h"
#include "InPitchingSubState.h"
#include "WaitingPitchingSubState.h"
#include <cmath>

#include <algorithm>

#include"TitleScreenState.h"


class Vector2D {
public:
    Vector2D(float x, float y) :x(x), y(y) {}
    float x;
    float y;
    float norm()const {
        return sqrt(x * x + y * y);
    }
    void normalize() {
        if (norm() == 0) {
            return;
        }
        float r = norm();
        x = x / r;
        y = y / r;
    }
    void scalar(float r) {
        x = r * x;
        y = r * y;
    }
};


PlayingState::PlayingState(Game& game):
    GameState(game)
{
    //GameObject�̃C���X�^���X�𐶐�
    appendObject(L"PICTURE_FIELD", L".//assets//�t�B�[���h.bmp", { 1152,720 });
    appendObject(L"PICTURE_BATTER", L".//assets//�Ŏ�.bmp", { 360,391 });
    appendObject(L"BUTTON_EXIT", L".//assets//�����.bmp", { 256,128 });
    appendObject(L"PICTURE_PITCHER", L".//assets//����X�v���C�g�V�[�g.bmp", { 168,266 });
    appendObject(L"PICTURE_BALL", L".//assets//�{�[��.bmp", { 41,50 });
    appendObject(L"JUDGE_BAT", L".//assets//battingJudgeFrame.bmp", { 50,50 });//�o�b�g�����蔻��

    getGameObject(L"PICTURE_BALL").hide();
    gameObjects.at(L"JUDGE_BAT").hide();

    //�eGameObject�̕`��ʒu��ݒ�
    gameObjects.at(L"PICTURE_FIELD").setObjectPosition({ 0,0 });
    gameObjects.at(L"PICTURE_BATTER").setObjectPosition({ 32,48 });
    gameObjects.at(L"BUTTON_EXIT").setObjectPosition({ 850,500 });
    gameObjects.at(L"PICTURE_PITCHER").setObjectPosition({ 514, 22 });
    
    initializeStartTime();

    changeSubState(new WaitingPitchingSubState(*this));

    OutputDebugString(L"PlayingState�̃C���X�^���X���쐬����܂���\n");
}

void PlayingState::update(Game& game) {
    if (currentSubState)currentSubState->update(game);
}

void PlayingState::updateBatFrame(int currentBatterFrame)
{
    POINT batterPos = gameObjects.at(L"PICTURE_BATTER").getPosition();
    //�o�b�g����g�ړ�
    POINT framePos = { getCursorPos().x - 25,
        getCursorPos().y - 25 - (currentBatterFrame - 3) * 25 };
    gameObjects.at(L"JUDGE_BAT").setObjectPosition(framePos);
    //�o�b�g����g�̏o��
    gameObjects.at(L"JUDGE_BAT").appear();
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

void PlayingState::updateBatterPos(const InputManager& inputManager)
{
    POINT nextKamayamaPos = { 0,0 };//���t���[���̑Ŏ҂̍��W

    //�}�E�X���W���擾���A���R�̍��W��ύX
    const POINT mouse = inputManager.getMousePosition();
    Vector2D velocityAngle(mouse.x - getCursorPos().x,
        mouse.y - getCursorPos().y);//���x�x�N�g���i���������Ӗ��������Ȃ��j


    
    if (velocityAngle.norm() < batterMovementSpeed) {//�|�C���^�[�ƃo�b�e�B���O�J�[�\�����߂�
        nextKamayamaPos = { mouse.x - 302,mouse.y - 197 };
    }
    else {
        velocityAngle.normalize();
        velocityAngle.scalar((float)batterMovementSpeed);


        nextKamayamaPos = PlayingState::nextKamayamaPos(gameObjects.at(L"PICTURE_BATTER").getPosition(), velocityAngle);//���t���[���̊��R�̈ʒu
    }
    
    gameObjects[L"PICTURE_BATTER"].setObjectPosition(nextKamayamaPos);
}

const POINT PlayingState::getCursorPos() const
{
    const POINT batterPos = getConstGameObject(L"PICTURE_BATTER").getPosition();
    POINT cursorPos = { batterPos.x+302,batterPos.y+197};
    return cursorPos;
}

void PlayingState::initializeStartTime()
{
    phaseStartTime = GetTickCount64();
}

bool PlayingState::calculateMeet(Ball& ball)
{
    POINT cursorPos = getCursorPos();
    POINT ballPos = getGameObject(L"PICTURE_BALL").getPosition();
    if (abs(cursorPos.x - ballPos.x) > 50) {
        //x���W������
        return false;
    }
    if (abs(cursorPos.y - ballPos.y) > 50) {
        //y���W������
        return false;
    }
    //���������̂Ń{�[���̑��x���v�Z
    int speed = 50 - abs(cursorPos.x - ballPos.x);
    getBall().setSpeed(speed);
    int angle = std::round( - 9 * (float(ballPos.y) - float(cursorPos.y)) / 5);
    getBall().setSpeed(angle);
    //�Ō��true
    return true;
}

Ball& PlayingState::getBall()
{
    return ball;
}

void PlayingState::updateWaitingPitchingTimer()
{
    ULONGLONG currentTime = GetTickCount64();
    waitingPitchingTimer = currentTime - phaseStartTime;
}


void PlayingState::hitting()
{
    POINT ballPos = gameObjects.at(L"PICTURE_BALL").getPosition();
    POINT batterPos = gameObjects.at(L"PICTURE_BATTER").getPosition();

    

    if (abs(ballPos.y - batterPos.y) < 50&&
        abs(ballPos.x - batterPos.x) < 50) {//�{�[���ƃo�b�g���߂�
        //�o�b�g�ƃ{�[������������
        OutputDebugString(L"�q�b�g\n");

        //����


        return;

    }
    OutputDebugStringW(L"��U��\n");
}

POINT PlayingState::nextKamayamaPos(POINT position, Vector2D movement)
{
    POINT nextPos = { 0,0 };
    nextPos.x = std::max<int>(batterBox.left, std::min<int>(position.x + (int)std::round(movement.x), batterBox.right));
    nextPos.y = std::max<int>(batterBox.top, std::min<int>(position.y + (int)std::round(movement.y), batterBox.bottom));
    return nextPos;
}

void PlayingState::updatePitchingMotion()
{
    //�s�b�`���[����0�t���[��
}
