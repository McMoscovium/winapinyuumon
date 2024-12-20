#pragma once

#include "PitchType/PitchType.h"
#include "Windows.h"

class Slider : public PitchType
{
private:
	LONG startCurvingY = 400;//�J�[�u�J�nY���W
	float diff = -4.0f;//�܂��肮����
public:
	Slider() :
		PitchType(L"SLIDER") {
	}
	void update(Ball& ball, int frame) override;
	float decideAngle() override;
};