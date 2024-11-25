#pragma once
#include "Stage.h"

class SasakiStage :
    public Stage
{
public:
    SasakiStage();
    ~SasakiStage() = default;

    std::unique_ptr<Pitcher> createPitcher()override;
    std::unique_ptr<Batter> createBatter()override;
    std::unique_ptr<Stadium> createStadium()override;
};

