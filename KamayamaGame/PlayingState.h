#pragma once

#include"GameState.h"

#include <string>
#include <vector>
#include "Ball.h"
#include "Vector2D.h"
#include <unordered_map>
#include "Result.h"

class pitcher;
class Batter;
class Game;
class InputManager;
class Stadium;

class PlayingState :
    public GameState<PlayingState,GameSubState<PlayingState>>
{
public:
    PlayingState(Game& game, Batter* batter, Pitcher* pitcher, Stadium* stadium, int trials);
    ~PlayingState();

    enum FlyBallResult {
        HOMERUN,
        FOUL,
        HIT,
        STRIKE
    };


    //�A�b�v�f�[�g�֐�
    //�Q�[�����I��������GameOverState�ɑJ��
    void update(Game& game)override;
    void updateBatFrame(int currentBatterFrame);
    //�o�b�^�[�̃A�j���[�V�����X�V
    void updateBatterAnimation(const InputManager& inputManager);
    //�o�b�^�[�̈ʒu�X�V
    void updateBatterPos(const InputManager& inputManager);
    //
    const POINT getCursorPos()const;
    //�t�F�C�Y�J�n���̎������L�^
    void initializeStartTime();
    //
    int& getRestBalls();
    //
    Ball& getBall();
    //
    Batter* getBatter();
    //
    Pitcher* getPitcher();
    //
    Stadium* getStadium();
    int& getDistance();
    //
    std::unordered_map<std::wstring, GameObject&>& getFieldImages();
    //
    Result& getResult();
    //�o�b�^�[�̈ʒu��pos�ɂ���Bpos���o�b�^�[�{�b�N�X����͂ݏo�Ă�����{�b�N�X�ɂ����B
    void setBatterInBox(POINT pos);


private:
    Ball ball;
    Pitcher* pitcher;
    Batter* batter;
    Stadium* stadium;
    //�c�苅��
    int restBalls;
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
    //�򋗗����L�^����ϐ�
    int distance = 0;
    //�t�B�[���h�摜�ւ̎Q�Ƃ̗�
    std::unordered_map<std::wstring, GameObject&> fieldImages;
    //
    Result result;


    //
    void updateWaitingPitchingTimer();

    //�X�C���O���̃q�b�e�B���O����
    void hitting();
    //
    POINT nextKamayamaPos(POINT position, Vector2D<float> movement);
    //
    void updatePitchingMotion();
};