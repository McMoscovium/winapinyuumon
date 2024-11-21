#include "TheHundredAcreWoodStadium.h"
#include <string>

PlayingState::FlyBallResult TheHundredAcreWoodStadium::result(POINT pos)
{
	OutputDebugString((L"x: " + std::to_wstring(pos.x) + L"\n").c_str());
	OutputDebugString((L"y: " + std::to_wstring(pos.y) + L"\n").c_str());
	if (abs(std::atan2(pos.x,-pos.y)) > 1.0255f) {
		//�t�@�E��
		return PlayingState::FlyBallResult::FOUL;
	}
	//�ȉ��A�t�F�A�]�[���ɗ�����
	if (pos.x < -1940) {
		//���t�g��
		return PlayingState::HOMERUN;
	}
	if (pos.x > 1810) {
		//���C�g��
		return PlayingState::HOMERUN;
	}
	if (pos.x < -1137) {
		//������
		if ((-2895435 - 1002 * pos.x) / 803 > pos.y) {
			return PlayingState::HOMERUN;
		}
		return PlayingState::HIT;
	}
	if (pos.x > 1025) {
		//�E����
		if (pos.y < (1099 * pos.x - 2843270) / 785) {
			return PlayingState::HOMERUN;
		}
		return PlayingState::HIT;
	}
	//�Z���^�[����
	if (pos.y < -2187) {
		return PlayingState::HOMERUN;
	}
	return PlayingState::HIT;
}
