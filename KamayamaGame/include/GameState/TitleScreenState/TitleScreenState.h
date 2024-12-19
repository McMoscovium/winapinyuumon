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
    //状態を更新
    //スタートボタンが押されたらPlayingStateに遷移
    void update(Game& game)override;

	void enter(Game& game)override;
	void exit(Game& game)override;
};