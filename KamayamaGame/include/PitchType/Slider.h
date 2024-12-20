#pragma once

#include "PitchType/PitchType.h"
#include "Windows.h"

class Slider : public PitchType
{
private:
	LONG startCurvingY = 400;//カーブ開始Y座標
	float diff = -4.0f;//まがりぐあい
public:
	Slider() :
		PitchType(L"SLIDER") {
	}
	void update(Ball& ball, int frame) override;
	float decideAngle() override;
};