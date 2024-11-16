#pragma once
#include "GameSubState.h"

#include "PlayResultState.h"
#include <string>

class CompareNormSubState :
    public GameSubState<PlayResultState>
{
private:
    int clearPictureFrame = 0;//�u�N���A�I�v�u�����ς�...�v�摜�̃A�j���[�V�����Ɏg��
    std::wstring clearPictureName = L"";
public:
    CompareNormSubState(PlayResultState& owner) :
        GameSubState(owner) {
        if (owner.getResult().isClear()) {
            clearPictureName = L"PICTURE_CLEAR";
        }
        else {
            clearPictureName = L"PICTURE_FAILURE";
        }
    }
    ~CompareNormSubState() = default;

    void update(Game& game)override;
    void enter(Game& game)override;
    void exit(Game& game)override;
};

