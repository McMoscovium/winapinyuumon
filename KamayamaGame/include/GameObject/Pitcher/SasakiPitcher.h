#pragma once
#include "GameObject/Pitcher/Pitcher.h"

#include "resource.h"

using namespace std;

class SasakiPitcher :
    public Pitcher
{
private:
    bool isOddFrame = false;
public:
    SasakiPitcher(HINSTANCE hInstance) :
        Pitcher(
            L"ç≤ÅXñÿòNäÛ",
            30,
            27,
            IDB_BITMAP38,
            hInstance,
            SIZE{200,266}
            ) {}
    void decideNextPitch()override;
    bool nextFrame()override;
};

