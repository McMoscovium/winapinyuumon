#pragma once
#include "GameState.h"

#include "Result.h"
#include "PictureObject.h"
#include "TextObject.h"

class Pitcher;

class PlayResultState :
    public GameState<PlayResultState,GameSubState<PlayResultState>>
{
private:
    Result& result;

public:
    PlayResultState(Game& game, Result& result,Pitcher* pitcher);
    ~PlayResultState();

    void update(Game& game)override;

    const Result& getResult()const;
};