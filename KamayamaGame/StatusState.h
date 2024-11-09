#pragma once
#include "GameState.h"

class Game;
class InputManager;

class StatusState :
    public GameState<StatusState>
{
    using SubStateType = GameSubState<StatusState>;
public:
    //�R���X�g���N�^
    StatusState(Game& game);

    void update()override;
};

