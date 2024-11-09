#pragma once

#include <Windows.h>
#include <memory>

class Timer
{
public:
	Timer();

	//生成されてからの時間を更新
	void update();
	//生成されてからの時間を返す
	ULONGLONG getTime()const;
	//生成されてからの時間をレコードに記録
	void recordTime();
	//レコードを返す
	ULONGLONG getRecord()const;
	//現在時刻とレコードの差を返す
	ULONGLONG span()const;
	//
	bool operator>(ULONGLONG)const;
private:
	ULONGLONG time;
	ULONGLONG record;
};