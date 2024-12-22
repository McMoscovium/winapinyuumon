#pragma once
#include "GameState/GameState.h"

class Game;

class StageListState :
    public GameState<StageListState,GameSubState<StageListState>>
{
private:
    char openedStages;
    static const char MAX_STAGES = 8;
public:
    StageListState(Game& game, AudioManager& audioManager, char openedStages);

    void update(Game& game)override;
	void enter(Game& game)override;
	void exit(Game& game)override;
};