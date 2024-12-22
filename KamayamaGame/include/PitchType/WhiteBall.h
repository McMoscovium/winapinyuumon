#pragma once

#include "PitchType/PitchType.h"

class Pitcher;

class WhiteBall : public PitchType
{
private:
	int depth;//‚¬‚´‚¬‚´‚Ì‘å‚«‚³
	int frequency;//‚¬‚´‚¬‚´‚ÌŒü‚«‚ð•Ï‚¦‚é•p“x
public:
	WhiteBall();
	~WhiteBall() = default;
	void update(Ball& ball, int frame) override;
	virtual float decideAngle() override;
	virtual float decideHVelocity() override { return (float)depth; }
	int decideVelocity(Pitcher& pitcher)override;
};