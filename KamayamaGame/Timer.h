#pragma once

#include <Windows.h>

class Timer
{
public:
	Timer();

	//time‚ğŒ»İ‚ÉXV
	void update();
	//Œ»İ‚ğrecord‚É‹L˜^
	void setRecord();
	//record‚Ætime‚Ì·‚ğ•Ô‚·
	ULONGLONG span();
private:
	ULONGLONG time;
	ULONGLONG record;
};

