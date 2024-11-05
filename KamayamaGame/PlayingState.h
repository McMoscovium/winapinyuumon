#pragma once

#include"GameState.h"

#include <string>
#include <vector>

class Game;
class InputManager;
class Vector2D;

class PlayingState :
    public GameState
{
public:
    enum Phase {
        WAITING_PITCHING,
        IN_PITCHING,
        BALL_FLYING
    };

    

    PlayingState();

    //�A�b�v�f�[�g�֐�
    //�Q�[�����I��������GameOverState�ɑJ��
    void update(Game* game,InputManager* inputManager)override;
    void updateWaitingPitchingPhase(InputManager* inputManager, Game* game);
    void updateBatFrame(int currentBatterFrame);
    void updateInPitchingPhase(InputManager* inputManager, Game* game);
    void updateCursorPos(InputManager* inputManager);
    //�o�b�^�[�̃A�j���[�V�����X�V
    void updateBatterAnimation(InputManager* inputManager);
    //�o�b�^�[�̈ʒu�X�V
    void updateBatterPos(InputManager* inputManager);
    //
    const POINT getCursorPos()const;
    //�t�F�C�Y�J�n���̎������L�^
    void initializeStartTime();

private://�����o�ϐ�
    //animateBatter()�Ɏg���ϐ�
    bool releasedLeftButtonUntilSwingEnded = false;
    //�o�b�^�[�̈ړ��X�s�[�h
    int batterMovementSpeed = 10;
    //�o�b�^�[���ړ��\�Ȕ͈�
    const RECT batterBox = { 178,266,355,357 };
    //�q�b�e�B���O�J�[�\���̈ʒu
    POINT cursorPos = { 0,0 };
    //�t�F�[�Y
    Phase phase = WAITING_PITCHING;
    //�t�F�[�Y�J�n����
    DWORD phaseStartTime = 0;
    //WAITING_PITCHING�p�^�C�}�[
    DWORD waitingPitchingTimer = 0;
    //
    void updateWaitingPitchingTimer();
    //
    void changePhase(Phase phase);

    //�X�C���O���̃q�b�e�B���O����
    void hitting();
    //
    POINT nextKamayamaPos(POINT position, Vector2D movement);
    //
    void updatePitchingMotion();
};