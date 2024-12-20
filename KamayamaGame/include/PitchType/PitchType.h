#pragma once

#include <string>

class Ball;

//����N���X
class PitchType
{
private:
	std::wstring typeName;
public:
	PitchType(std::wstring typeName) :
		typeName(typeName) {}
	virtual ~PitchType() = default;

	//���݂̋���ƃ����[�X����Ă���̃t���[�����ɏ]���{�[���̑��x���v�Z
	virtual void update(Ball& ball, int frame) = 0;
};

