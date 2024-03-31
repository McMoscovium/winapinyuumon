#pragma once

#include<Windows.h>
#include"Window.h"

class Game
{
private:
	Window window;
	
public:
	enum SeqName {
		SEQ_TITLE
	};

	void initializeWindow(LPCSTR name, LPCSTR iconPath, LPCSTR sysIconPath, SeqName SEQ_NAME);
	bool terminateFlag();
	void mainloop();
	void terminate();
};