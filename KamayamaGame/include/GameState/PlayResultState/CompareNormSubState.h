#pragma once
#include "GameState/GameSubState.h"

#include "GameState/PlayResultState/PlayResultState.h"
#include <string>

class CompareNormSubState :
    public GameSubState<PlayResultState>
{
private:
    int clearPictureFrame = 0;//「クリア！」「しっぱい...」画像のアニメーションに使う
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

