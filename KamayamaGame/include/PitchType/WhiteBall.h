#pragma once

#include "PitchType/PitchType.h"

class Pitcher;

class WhiteBall : public PitchType
{
private:
	int depth;//ぎざぎざの大きさ
	int frequency;//ぎざぎざの向きを変える頻度
public:
	WhiteBall();
	~WhiteBall() = default;
	void update(Ball& ball, int frame) override;
	virtual float decideAngle() override;
	virtual float decideHVelocity() override { return (float)depth; }
	int decideVelocity(Pitcher& pitcher)override;
};