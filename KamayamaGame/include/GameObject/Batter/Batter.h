#pragma once

#include "GameObject/PictureObject.h"
#include "Skill/Skill.h"

#include <string>
#include <Windows.h>

class Skill;

class Batter :
	public PictureObject
{
protected:
	std::wstring name;
	int power;
	float speed;
	float meet;
	Skill skill;
public:
	const std::wstring path;
	const SIZE frameSize;

	Batter(const std::wstring& batterName, int power, float speed, float meet, const std::wstring& path, const SIZE& frameSize);
	Batter(const std::wstring& batterName, int power, float speed, float meet, const int resourceId, HINSTANCE hInstance, const SIZE& frameSize);
	virtual ~Batter() = default;

	//
	std::wstring getName()const;
	//
	int getPower()const;
	//
	float getMeet()const;
	//
	float getSpeed()const;
};