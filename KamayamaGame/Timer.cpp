#include "Timer.h"

#include <Windows.h>

ULONGLONG Timer::getTime()const
{
	return time;
}

void Timer::recordTime()
{
	record = GetTickCount64();
}

ULONGLONG Timer::getRecord()const
{
	return record;
}

ULONGLONG Timer::span() const
{
	return getTime() - getRecord();
}

bool Timer::operator>(ULONGLONG compared) const
{
	return time > compared;
}

Timer::Timer():
	time(GetTickCount64()),
	record(GetTickCount64())
{
}

void Timer::update()
{
	time = GetTickCount64();
}

