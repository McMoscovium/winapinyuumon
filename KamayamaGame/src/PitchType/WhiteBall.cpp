#include "PitchType/WhiteBall.h"

#include "GameObject/Ball.h"
#include <random>

WhiteBall::WhiteBall() :
	PitchType(L"WhiteBall"),
	depth(20),
	frequency(4)
{
}

void WhiteBall::update(Ball& ball, int frame)
{
	if (frame == 2) {
		ball.sethVelocity(20);
		return;
	}


	//frequencyフレームごとにぎざぎざの向きを変える
	bool isChangeFrame = frame % frequency == 0;//フレーム数が5の倍数のとき曲がる
	if (!isChangeFrame) return;

	float currentHVelocity = ball.getHVelocity();
	float nextHVelocity = 0;
	bool arity = frame % (frequency * 2) == 0;
	if (arity) {
		nextHVelocity = currentHVelocity + depth * 2;
	}
	else {
		nextHVelocity = currentHVelocity - depth * 2;
	}
	OutputDebugString((L"nextHVelocity:" + std::to_wstring(nextHVelocity) + L"\n").c_str());
	ball.sethVelocity(nextHVelocity);
}

float WhiteBall::decideAngle()
{
	std::random_device rd;
	std::mt19937 gen(rd()); // メルセンヌ・ツイスタ乱数生成器
	std::uniform_real_distribution<float> dis(-7.0f, 7.0f);

	return dis(gen);
}
