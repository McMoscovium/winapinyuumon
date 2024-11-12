#pragma once

#include "GameState.h"
#include <vector>
#include <string>

class InputManager;
class Game;

class TitleScreenState :
    public GameState<TitleScreenState,GameSubState<TitleScreenState>>
{
public:
    TitleScreenState(Game& game);
    //��Ԃ��X�V
    //�X�^�[�g�{�^���������ꂽ��PlayingState�ɑJ��
    void update(Game& game)override;
};