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


    //�X�e�[�^�X���A�b�v������
    //�X�e�[�^�X�ɕω�����Ȃ�true
    bool statusUp(char& status, char& filled, int& money,int & neededMoney, HatimituMeterObject& meter) {
        if (status >= 30) {
            //���łɃX�e�[�^�X��MAX
            return false;
        }
        if (status == filled && money < neededMoney) {
            //�V�K�w��������������������Ȃ�
            return false;
        }
        if (status < filled) {
            //�V�K�w��������UP
            meter.addValue();
            status++;
            return true;
        }
        //�V�K�w��
        meter.addValue();
        status++;
        filled++;
        money -= neededMoney;
        neededMoney = status * 1000;
        return true;
    }
public:
    //�R���X�g���N�^
    StatusState(Game& game);

    void update(Game& game)override;
};

