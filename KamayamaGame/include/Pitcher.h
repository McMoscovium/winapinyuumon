#pragma once

#include <string>
#include <vector>
#include <Windows.h>
#include "PitchType.h"
#include "Straight.h"
#include "PictureObject.h"

class Pitcher:
	public PictureObject
{
protected:
	std::wstring pitcherName;
	std::vector<PitchType*> pitchTypes;
	PitchType* nextPitch = nullptr;
	int armStrength;
	int pitchingSpeed = 0;
	//�p�x
	float pitchingCourse = 0;
	//���݂̋���̔ԍ�
	int currentPitchNumber = 0;

	bool isOddFrame = false;
	

public:
	//�{�[���������[�X����t���[��
	const int releaseFrame;
	//
	const std::wstring path;
	//
	SIZE frameSize;


	Pitcher(
		const std::wstring& pitcherName,
		int armStrength,
		int releaseFrame,
		const std::wstring& path,
		SIZE frameSize
	);
	virtual ~Pitcher();

	//
	int getArmStrength()const;
	//
	int getPitchingSpeed()const;
	float getPitchingAngle()const;
	//
	void setPitchingSpeed(int sp);
	//
	void setPitchingCourse(float c);
	//���݂̋�����擾
	PitchType* getPitchType();
	//
	const std::wstring& getName()const;
	//
	virtual bool nextFrame()override;
	
	//���̋���A�����A������R�[�X�������_���Ɍ���
	virtual void decideNextPitch() = 0;
};

