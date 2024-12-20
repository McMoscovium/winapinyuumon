#pragma once
#include "GameObject/Pitcher/Pitcher.h"
#include "PitchType/Slider.h"
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
            L"���X�ؘN��",
            30,
            27,
            IDB_BITMAP38,
            hInstance,
            SIZE{200,266}
            ) 
    {
		pitchTypes.push_back(new Slider());
        OutputDebugString(L"SasakiPitcher�ɃX���C�_�[�ǉ�\n");
    }
    void decideNextPitch()override;
    bool nextFrame()override;
};

