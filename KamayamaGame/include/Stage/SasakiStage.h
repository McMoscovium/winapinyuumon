#pragma once
#include "Stage/Stage.h"

class SasakiStage :
    public Stage
{
public:
    SasakiStage();
    ~SasakiStage() = default;

    std::unique_ptr<Pitcher> createPitcher(HINSTANCE hInstance)override;
    std::unique_ptr<Batter> createBatter(HINSTANCE hInstance)override;
    std::unique_ptr<Stadium> createStadium()override;
};

