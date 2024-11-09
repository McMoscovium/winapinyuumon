#pragma once
#include "GameSubState.h"

#include <memory>

class PlayingState;

class InPitchingSubState :
    public GameSubState<PlayingState>
{
public:
    InPitchingSubState(PlayingState& context);
    void update()override;
private:
    //�s�b�`���O���[�V�����̍X�V
    void updatePitchingMotion();
};