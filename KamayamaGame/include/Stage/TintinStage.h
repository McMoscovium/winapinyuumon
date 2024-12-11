#pragma once
#include "Stage/Stage.h"
class TintinStage :
    public Stage
{
public:
    TintinStage();
    ~TintinStage() = default;

    std::unique_ptr<Pitcher> createPitcher(HINSTANCE hInstance)override;
    std::unique_ptr<Batter> createBatter(HINSTANCE hInstance)override;
    std::unique_ptr<Stadium> createStadium()override;
};

