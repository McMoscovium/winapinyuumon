#pragma once
#include "Stage.h"
class TintinStage :
    public Stage
{
public:
    TintinStage();
    ~TintinStage() = default;

    std::unique_ptr<Pitcher> createPitcher()override;
    std::unique_ptr<Batter> createBatter()override;
    std::unique_ptr<Stadium> createStadium()override;
};

