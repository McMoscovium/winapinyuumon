#pragma once

#include "GameState.h"
#include <vector>
#include <string>
#include <memory>

class InputManager;
class Game;

class TitleScreenState :
    public GameState<TitleScreenState>
{
public:
    using SubStateType = GameSubState<TitleScreenState>;
    
    TitleScreenState(Game& game);

    //��Ԃ��X�V
    //�X�^�[�g�{�^���������ꂽ��PlayingState�ɑJ��
    void update()override;

private:
    //�����o�֐�
};