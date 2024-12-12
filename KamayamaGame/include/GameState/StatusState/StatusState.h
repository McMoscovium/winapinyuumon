#pragma once
#include "GameState/GameState.h"
#include "util/HatimituMeter.h"
#include "GameObject/PictureObject.h"

#include "Game/SaveData/SaveData.h"
#include "Skill/Skill.h"

#include <string>

class Game;
class InputManager;

class StatusState :
    public GameState<StatusState,GameSubState<StatusState>>
{
private:
    SaveData data;
    int neededPowerPoint;
    int neededMeetPoint;
    int neededSpeedPoint;

    bool allowModify = false;//����{�^���������邩


    //�Z�[�u�f�[�^���烁���o�ϐ���ݒ�
    void loadSaveData(const SaveData& saveData) {
        data = saveData;
        neededPowerPoint = data.getPower() * 1000;
        neededMeetPoint = data.getMeet() * 1000;
        neededSpeedPoint = data.getSpeed() * 1000;
    }

public:
    //�R���X�g���N�^
    StatusState(Game& game);

    void update(Game& game)override;
};

