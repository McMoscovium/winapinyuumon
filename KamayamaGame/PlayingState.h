#pragma once

#include"GameState.h"

#include <string>
#include <vector>

class Game;
class InputManager;

class PlayingState :
    public GameState
{
public:
    PlayingState();

    //�A�b�v�f�[�g�֐�
    //�Q�[�����I��������GameOverState�ɑJ��
    void update(Game* game,InputManager* inputManager)override;
    //�o�b�^�[�̃A�j���[�V�����X�V
    void animateBatter(InputManager* inputManager);
    //�o�b�^�[�̈ʒu�X�V
    void updateBatterPos(InputManager* inputManager);
private://�����o�ϐ�
    //animateBatter()�Ɏg���ϐ�
    bool releasedLeftButtonUntilSwingEnded = false;
    //�o�b�^�[�̈ړ��X�s�[�h
    int batterMovementSpeed = 1;
    //�o�b�^�[���ړ��\�Ȕ͈�
    const RECT batterBox = { 172,262,255,375 };
};