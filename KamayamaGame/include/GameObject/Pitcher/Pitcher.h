#pragma once

#include <string>
#include <vector>
#include <Windows.h>
#include "PitchType/PitchType.h"
#include "PitchType/Straight.h"
#include "GameObject/PictureObject.h"

class Pitcher:
	public PictureObject
{
protected:
	std::wstring pitcherName;
	std::vector<PitchType*> pitchTypes;
	int armStrength;
	int pitchingSpeed = 0;
	//角度
	float pitchingCourse = 0;
	//現在の球種の番号
	int currentPitchNumber = 0;

	bool isOddFrame = false;
	

public:
	//ボールをリリースするフレーム
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
	Pitcher(
		const std::wstring& pitcherName,
		int armStrength,
		int releaseFrame,
		const int resourceId,
		HINSTANCE hInstance,
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
	void setPitchingCourse(const float c);
	//現在の球種を取得
	PitchType* getPitchType();
	//
	const std::wstring& getName()const;
	//
	virtual bool nextFrame()override;
	
	//次の球種、球速、投げるコースをランダムに決定
	virtual void decideNextPitch() = 0;
};

