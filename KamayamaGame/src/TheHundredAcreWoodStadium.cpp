#include "TheHundredAcreWoodStadium.h"
#include <string>

PlayingState::FlyBallResult TheHundredAcreWoodStadium::result(POINT pos)
{
	OutputDebugString((L"x: " + std::to_wstring(pos.x) + L"\n").c_str());
	OutputDebugString((L"y: " + std::to_wstring(pos.y) + L"\n").c_str());
	if (abs(std::atan2(pos.x,-pos.y)) > 1.0255f) {
		//ファウル
		return PlayingState::FlyBallResult::FOUL;
	}
	//以下、フェアゾーンに落ちた
	if (pos.x < -1940) {
		//レフト線
		return PlayingState::HOMERUN;
	}
	if (pos.x > 1810) {
		//ライト線
		return PlayingState::HOMERUN;
	}
	if (pos.x < -1137) {
		//左中間
		if ((-2895435 - 1002 * pos.x) / 803 > pos.y) {
			return PlayingState::HOMERUN;
		}
		return PlayingState::HIT;
	}
	if (pos.x > 1025) {
		//右中間
		if (pos.y < (1099 * pos.x - 2843270) / 785) {
			return PlayingState::HOMERUN;
		}
		return PlayingState::HIT;
	}
	//センター方向
	if (pos.y < -2187) {
		return PlayingState::HOMERUN;
	}
	return PlayingState::HIT;
}
