#pragma once
#include "GameState.h"

#include "Result.h"
#include "PictureObject.h"
#include "TextObject.h"

class Stage;

class PlayResultState :
    public GameState<PlayResultState,GameSubState<PlayResultState>>
{
private:
    Result& result;

public:
    PlayResultState(Game& game, Result& result,Stage* stage);
    ~PlayResultState();

    void update(Game& game)override;

    const Result& getResult()const;
};