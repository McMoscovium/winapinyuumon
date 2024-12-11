#pragma once
#include "GameState/GameState.h"
#include "util/HatimituMeter.h"
#include "GameObject/PictureObject.h"

class Game;
class InputManager;

class StatusState :
    public GameState<StatusState,GameSubState<StatusState>>
{
private:
public:
    //�R���X�g���N�^
    StatusState(Game& game);

    void update(Game& game)override;
};

