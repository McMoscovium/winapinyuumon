#pragma once
#include "GameState/GameState.h"

#include "util/Result.h"
#include "GameObject/PictureObject.h"
#include "GameObject/TextObject.h"
#include "Game/SaveData/SaveData.h"

class Stage;

class PlayResultState :
    public GameState<PlayResultState,GameSubState<PlayResultState>>
{
private:
    Result& result;
    SaveData saveData;
    char openedStages;
    
public:
    PlayResultState(Game& game, AudioManager& audioManager, Result& result,const int trials, const int norm, const std::wstring& pitcherName, const char stageNumber, const float scoreFactor);
    ~PlayResultState();

    void update(Game& game)override;
	void enter(Game& game)override;
	void exit(Game& game)override;

    const Result& getResult()const;
    char getOpenedStages()const { return openedStages; }
};