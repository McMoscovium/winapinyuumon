#pragma once

#include"GameState.h"

#include <string>
#include <vector>

class Game;
class InputManager;
class Vector2D;

class PlayingState :
    public GameState<PlayingState,GameSubState<PlayingState>>
{
public:
    PlayingState(Game& game);

    //�A�b�v�f�[�g�֐�
    //�Q�[�����I��������GameOverState�ɑJ��
    void update(Game& game)override;
    void updateWaitingPitchingPhase(InputManager* inputManager, Game* game);
    void updateBatFrame(int currentBatterFrame);
    //�o�b�^�[�̃A�j���[�V�����X�V
    void updateBatterAnimation(const InputManager& inputManager);
    //�o�b�^�[�̈ʒu�X�V
    void updateBatterPos(const InputManager& inputManager);
    //
    const POINT getCursorPos()const;
    //�t�F�C�Y�J�n���̎������L�^
    void initializeStartTime();

private://�����o�ϐ�
    //animateBatter()�Ɏg���ϐ�
    bool releasedLeftButtonUntilSwingEnded = false;
    //�o�b�^�[�̈ړ��X�s�[�h
    int batterMovementSpeed = 4;
    //�o�b�^�[���ړ��\�Ȕ͈�
    const RECT batterBox = { 178,266,355,357 };
    //�q�b�e�B���O�J�[�\���̈ʒu
    POINT cursorPos = { 0,0 };
    //�t�F�[�Y�J�n����
    ULONGLONG phaseStartTime = 0;
    //WAITING_PITCHING�p�^�C�}�[
    ULONGLONG waitingPitchingTimer = 0;
    //
    void updateWaitingPitchingTimer();

    //�X�C���O���̃q�b�e�B���O����
    void hitting();
    //
    POINT nextKamayamaPos(POINT position, Vector2D movement);
    //
    void updatePitchingMotion();
};