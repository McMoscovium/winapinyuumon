#pragma once

#include"GameState.h"

#include <string>
#include <vector>

class Game;
class InputManager;

class PlayingState :
    public GameState
{
public://�����o�ϐ�
private://�����o�ϐ�
    bool releasedLeftButtonUntilSwingEnded = false;

public://�����o�֐�
    PlayingState();
    //�A�b�v�f�[�g�֐�
    //�Q�[�����I��������GameOverState�ɑJ��
    void update(Game* game,InputManager* inputManager)override;

private:
};