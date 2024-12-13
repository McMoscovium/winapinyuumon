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

    bool allowModify = false;//決定ボタンを押せるか


    //セーブデータからメンバ変数を設定
    void loadSaveData(const SaveData& saveData) {
        data = saveData;
        neededPowerPoint = data.getPower() * 1000;
        neededMeetPoint = data.getMeet() * 1000;
        neededSpeedPoint = data.getSpeed() * 1000;
    }


    //ステータスをアップさせる
    //ステータスに変化あるならtrue
    bool statusUp(char& status, char& filled, int& money,int & neededMoney, HatimituMeterObject& meter) {
        if (status >= 30) {
            //すでにステータスがMAX
            return false;
        }
        if (status == filled && money < neededMoney) {
            //新規購入したいがお金が足りない
            return false;
        }
        if (status < filled) {
            //新規購入無しでUP
            meter.addValue();
            status++;
            return true;
        }
        //新規購入
        meter.addValue();
        status++;
        filled++;
        money -= neededMoney;
        neededMoney = status * 1000;
        return true;
    }
public:
    //コンストラクタ
    StatusState(Game& game);

    void update(Game& game)override;
};

