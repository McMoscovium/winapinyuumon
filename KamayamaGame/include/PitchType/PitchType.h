#pragma once

#include <string>

class Ball;

//球種クラス
class PitchType
{
private:
	std::wstring typeName;
public:
	PitchType(std::wstring typeName) :
		typeName(typeName) {}
	virtual ~PitchType() = default;

	//現在の球種とリリースされてからのフレーム数に従いボールの速度を計算
	//基本的にvelocityとhVelocity、angleのみ更新する
	virtual void update(Ball& ball, int frame) = 0;
	virtual float decideAngle() = 0;
};

