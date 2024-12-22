#pragma once
#include "GameObject/Pitcher/Pitcher.h"

#include "PitchType/AccelBall.h"
#include "PitchType/WhiteBall.h"

#include "resource.h"

class TintinPitcher :
    public Pitcher
{
private:
public:
    TintinPitcher(HINSTANCE hInstance) :
        Pitcher(
            L"tintin",
            15, 34,
            IDB_BITMAP43,
            hInstance,
            SIZE{168,266}
        )
    {
		pitchTypes.push_back(new AccelBall());
		pitchTypes.push_back(new WhiteBall());
    }

    void decideNextPitch()override;
};

