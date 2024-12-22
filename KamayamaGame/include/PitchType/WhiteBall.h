#pragma once

#include "PitchType/PitchType.h"

class Pitcher;

class WhiteBall : public PitchType
{
private:
	int depth;//���������̑傫��
	int frequency;//���������̌�����ς���p�x
public:
	WhiteBall();
	~WhiteBall() = default;
	void update(Ball& ball, int frame) override;
	virtual float decideAngle() override;
	virtual float decideHVelocity() override { return (float)depth; }
	int decideVelocity(Pitcher& pitcher)override;
};