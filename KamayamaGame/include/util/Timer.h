#pragma once

#include <Windows.h>

class Timer
{
public:
	Timer();

	//time�����ݎ����ɍX�V
	void update();
	//���ݎ�����record�ɋL�^
	void setRecord();
	//record��time�̍���Ԃ�
	ULONGLONG span();
private:
	ULONGLONG time;
	ULONGLONG record;
};

