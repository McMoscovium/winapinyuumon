#pragma once

#include "GameState/GameState.h"

#include "GameObject/PictureObject.h"

class InputManager;
class Game;

class TitleScreenState :
    public GameState<TitleScreenState,GameSubState<TitleScreenState>>
{
private:
public:
    TitleScreenState(Game& game, AudioManager& audioManager);
	~TitleScreenState();
    //��Ԃ��X�V
    //�X�^�[�g�{�^���������ꂽ��PlayingState�ɑJ��
    void update(Game& game)override;

	void enter(Game& game)override;
	void exit(Game& game)override;
};