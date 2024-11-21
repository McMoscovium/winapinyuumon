#include "Timer.h"

#include<Windows.h>

Timer::Timer():
	time(GetTickCount64()),
	record(time)
{
}

void Timer::update()
{
	time = GetTickCount64();
}

void Timer::setRecord()
{
	record = time;
}

ULONGLONG Timer::span()
{
	return time - record;
}
