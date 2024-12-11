#pragma once
#include "GameObject/Pitcher/Pitcher.h"
#include "resource.h"

class TintinPitcher :
    public Pitcher
{
private:
public:
    TintinPitcher(HINSTANCE hInstance) :
        Pitcher(
            L"tintin",
            20, 34,
            IDB_BITMAP43,
            hInstance,
            SIZE{168,266}
        ) {}

    void decideNextPitch()override;
};

