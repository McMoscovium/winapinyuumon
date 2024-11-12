#pragma once
#include "Pitcher.h"
class Tintin :
    public Pitcher
{
private:
public:
    Tintin() :
        Pitcher(L"Tintin", 30) {}

    void decideNextPitch()override;
};

