#pragma once

#include <Windows.h>

class Timer
{
public:
	Timer();

	//timeを現在時刻に更新
	void update();
	//現在時刻をrecordに記録
	void setRecord();
	//recordとtimeの差を返す
	ULONGLONG span();
private:
	ULONGLONG time;
	ULONGLONG record;
};

