#pragma once

#include "GameState.h"
#include <vector>
#include <string>

class InputManager;
class Game;

class TitleScreenState :
    public GameState
{
public:
    //�����o�ϐ�

private:
    //�����o�ϐ�

public:
    //�����o�֐�

    TitleScreenState();

    //��Ԃ��X�V
    //�X�^�[�g�{�^���������ꂽ��PlayingState�ɑJ��
    void update(Game* game, InputManager* inputManager)override;

private:
    //�����o�֐�
};