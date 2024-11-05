#include "PlayingState.h"

#include "Game.h"
#include "GameOverState.h"
#include "InputManager.h"

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


PlayingState::PlayingState()
{
    //GameObject�̃C���X�^���X�𐶐�
    appendObject(L"PICTURE_FIELD", L".//assets//�t�B�[���h.bmp", { 1152,720 });
    appendObject(L"PICTURE_BATTER", L".//assets//�Ŏ�.bmp", { 360,391 });
    appendObject(L"BUTTON_EXIT", L".//assets//�����.bmp", { 256,128 });
    appendObject(L"PICTURE_PITCHER", L".//assets//����.bmp", { 112,182 });
    appendObject(L"PICTURE_BALL", L".//assets//�{�[��.bmp", { 41,50 });
    appendObject(L"JUDGE_BAT", L".//assets//battingJudgeFrame.bmp", { 50,50 });//�o�b�g�����蔻��

    gameObjects.at(L"JUDGE_BAT")->hide();

    //�eGameObject�̕`��ʒu��ݒ�
    gameObjects.at(L"PICTURE_FIELD")->setObjectPosition({ 0,0 });
    gameObjects.at(L"PICTURE_BATTER")->setObjectPosition({ 32,48 });
    gameObjects.at(L"BUTTON_EXIT")->setObjectPosition({ 850,500 });
    gameObjects.at(L"PICTURE_PITCHER")->setObjectPosition({ 514, 22 });
    
    initializeStartTime();

    OutputDebugString(L"PlayingState�̃C���X�^���X���쐬����܂���\n");
}


void PlayingState::update(Game* game, InputManager* inputManager) {
    switch (phase) {
    case WAITING_PITCHING:
        updateWaitingPitchingPhase(inputManager, game);
        break;
    case IN_PITCHING:
        updateInPitchingPhase(inputManager, game);
    }
    
}

void PlayingState::updateWaitingPitchingPhase(InputManager* inputManager, Game* game)
{
    //�^�C�}�[�̍X�V
    updateWaitingPitchingTimer();
    //�^�C�}�[�̃`�F�b�N
    if (waitingPitchingTimer > 5000) {
        //�t�F�[�Y��IN_PITCHING�ɕύX
        changePhase(IN_PITCHING);
        return;
    }

    //�q�b�e�B���O�J�[�\���̈ʒu���X�V
    updateCursorPos(inputManager);

    //�v���C���̍X�V����

    if (isClicked(L"BUTTON_EXIT", inputManager)) {
        game->changeState(new TitleScreenState());
        return;
    }

    //�ȉ��ABUTTON_EXIT�N���b�N����

    //�o�b�^�[�̈ʒu���}�E�X�ʒu�ɍ��킹�ĕύX
    updateBatterPos(inputManager);

    //�X�C���O�̃A�j���[�V��������
    updateBatterAnimation(inputManager);


    int currentBatterFrame = gameObjects.at(L"PICTURE_BATTER")->getCurrentFrameNumber();
    //�Ō�����
    {
        if (2 <= currentBatterFrame && currentBatterFrame <= 4) {
            updateBatFrame(currentBatterFrame);
            hitting();
        }


        if (currentBatterFrame >= 5) {
            //�o�b�g����g�̏���
            gameObjects.at(L"JUDGE_BAT")->hide();
        }

    }
}

void PlayingState::updateBatFrame(int currentBatterFrame)
{
    POINT batterPos = gameObjects.at(L"PICTURE_BATTER")->getPosition();
    //�o�b�g����g�ړ�
    POINT framePos = { getCursorPos().x - 25,
        getCursorPos().y - 25 - (currentBatterFrame - 3) * 25 };
    gameObjects.at(L"JUDGE_BAT")->setObjectPosition(framePos);
    //�o�b�g����g�̏o��
    gameObjects.at(L"JUDGE_BAT")->appear();
}

void PlayingState::updateInPitchingPhase(InputManager* inputManager, Game* game)
{
    //�q�b�e�B���O�J�[�\���̈ʒu���X�V
    updateCursorPos(inputManager);

    //�v���C���̍X�V����

    if (isClicked(L"BUTTON_EXIT", inputManager)) {
        game->changeState(new TitleScreenState());
        return;
    }

    //�ȉ��ABUTTON_EXIT�N���b�N����

    //�o�b�^�[�̈ʒu���}�E�X�ʒu�ɍ��킹�ĕύX
    updateBatterPos(inputManager);

    //�X�C���O�̃A�j���[�V��������
    updateBatterAnimation(inputManager);


    int currentBatterFrame = gameObjects.at(L"PICTURE_BATTER")->getCurrentFrameNumber();
    //�Ō�����
    {
        if (2 <= currentBatterFrame && currentBatterFrame <= 4) {
            updateBatFrame(currentBatterFrame);
            hitting();
        }


        if (currentBatterFrame >= 5) {
            //�o�b�g����g�̏���
            gameObjects.at(L"JUDGE_BAT")->hide();
        }

    }
}

void PlayingState::updateCursorPos(InputManager* inputManager)
{
    cursorPos = { gameObjects.at(L"PICTURE_BATTER")->getPositionX() + 302,
    gameObjects.at(L"PICTURE_BATTER")->getPositionY() + 197};
}

void PlayingState::updateBatterAnimation(InputManager* inputManager)
{
    //���R�̃X�C���O����
    const int kamayamaFrame = gameObjects.at(L"PICTURE_BATTER")->getCurrentFrameNumber();
    if (kamayamaFrame == 0) {//�X�C���O���ĂȂ�
        if (inputManager->getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_PRESSED) {
            releasedLeftButtonUntilSwingEnded = false;
            gameObjects.at(L"PICTURE_BATTER")->nextFrame();
            //OutputDebugString(L"�X�C���O�J�n\n");
        }
    }
    else if (kamayamaFrame < gameObjects.at(L"PICTURE_BATTER")->getLength() - 1) {//�X�C���O�r��
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
}

void PlayingState::updateBatterPos(InputManager* inputManager)
{
    POINT nextKamayamaPos = { 0,0 };//���t���[���̑Ŏ҂̍��W

    //�}�E�X���W���擾���A���R�̍��W��ύX
    POINT mouse = inputManager->getMousePosition();
    Vector2D velocityAngle(mouse.x - getCursorPos().x,
        mouse.y - getCursorPos().y);//���x�x�N�g���i���������Ӗ��������Ȃ��j


    
    if (velocityAngle.norm() < batterMovementSpeed) {//�|�C���^�[�ƃo�b�e�B���O�J�[�\�����߂�
        nextKamayamaPos = { mouse.x - 302,mouse.y - 197 };
    }
    else {
        velocityAngle.normalize();
        velocityAngle.scalar((float)batterMovementSpeed);


        nextKamayamaPos = PlayingState::nextKamayamaPos(gameObjects.at(L"PICTURE_BATTER")->getPosition(), velocityAngle);//���t���[���̊��R�̈ʒu
    }
    
    std::wstring message = L"x: " + std::to_wstring(nextKamayamaPos.x) + L" y: " + std::to_wstring(nextKamayamaPos.y) + L"\n";

    OutputDebugString(message.c_str());
    
    gameObjects[L"PICTURE_BATTER"]->setObjectPosition(nextKamayamaPos);
}

const POINT PlayingState::getCursorPos() const
{
    return cursorPos;
}

void PlayingState::initializeStartTime()
{
    phaseStartTime = GetTickCount64();
}

void PlayingState::updateWaitingPitchingTimer()
{
    DWORD currentTime = GetTickCount64();
    waitingPitchingTimer = currentTime - phaseStartTime;
}

void PlayingState::changePhase(Phase phase)
{
    PlayingState::phase = phase;
}

void PlayingState::hitting()
{
    POINT ballPos = gameObjects.at(L"PICTURE_BALL")->getPosition();
    POINT batterPos = gameObjects.at(L"PICTURE_BATTER")->getPosition();

    

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
