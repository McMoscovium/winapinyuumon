#pragma once
#include "GameState.h"

#include "Result.h"
class PlayResultState :
    public GameState<PlayResultState,GameSubState<PlayResultState>>
{
private:
    Result& result;
public:
    PlayResultState(Game& game, Result& result);
    ~PlayResultState();

    void update(Game& game)override;
};