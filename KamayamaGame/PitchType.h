#pragma once

#include <string>


//����N���X
class PitchType
{
private:
	std::wstring typeName;
public:
	PitchType(std::wstring typeName) :
		typeName(typeName) {}
};

