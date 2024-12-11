#pragma once
#include "GameState/GameSubState.h"

#include "GameState/PlayResultState/PlayResultState.h"
#include <string>

class CompareNormSubState :
    public GameSubState<PlayResultState>
{
private:
    int clearPictureFrame = 0;//�u�N���A�I�v�u�����ς�...�v�摜�̃A�j���[�V�����Ɏg��
    std::string clearPictureName = "";
public:
    CompareNormSubState(PlayResultState& owner) :
        GameSubState<PlayResultState>(owner) {
        if (owner.getResult().isClear()) {
            clearPictureName = "CLEAR";
        }
        else {
            clearPictureName = "FAILURE";
        }
    }
    ~CompareNormSubState() = default;

    void update(Game& game)override;
    void enter(Game& game)override;
    void exit(Game& game)override;
};

