#pragma once

#include "GameState.h"
#include "Batter.h"
#include "Pitcher.h"

class Game;
class InputManager;

class PlayingState :
    public GameState<PlayingState>
{
public:
    using SubStateType = GameSubState<PlayingState>;

    PlayingState(Game& game);
    ~PlayingState() = default;

    //�A�b�v�f�[�g�֐�
    //�Q�[�����I��������GameOverState�ɑJ��
    void update()override;
    //
    void updateBatterAnimation(const InputManager& inputManager);
    
    //
    Batter& getBatter();
    //
    BatBoundingBox& getBoundingBox();


private:
    bool releasedLeftButtonUntilSwingEnded = false;
    //
    void updateWaitingPitchingTimer();
        
};