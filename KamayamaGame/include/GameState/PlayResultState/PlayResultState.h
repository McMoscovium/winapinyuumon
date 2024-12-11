#pragma once
#include "GameState/GameState.h"

#include "util/Result.h"
#include "GameObject/PictureObject.h"
#include "GameObject/TextObject.h"

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