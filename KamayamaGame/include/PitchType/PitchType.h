#pragma once

#include <string>

class Ball;

//����N���X
class PitchType
{
protected:
	std::wstring typeName;
	int initialVelocity;
public:
	PitchType(std::wstring typeName) :
		typeName(typeName),
		initialVelocity(0)
	{}
	virtual ~PitchType() = default;

	//���݂̋���ƃ����[�X����Ă���̃t���[�����ɏ]���{�[���̑��x���v�Z
	//��{�I��velocity��hVelocity�Aangle�̂ݍX�V����
	virtual void update(Ball& ball, int frame) = 0;
	virtual float decideAngle() = 0;
	virtual float decideHVelocity() = 0;

	void setInitialVelocity(int v) {
		initialVelocity = v;
	}
};

