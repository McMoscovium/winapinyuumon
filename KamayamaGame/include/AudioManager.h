#pragma once

#include <string>

class AudioManager
{
private:
public:
	void play(const std::string& alias, const std::string& wavName, bool loop);
	void stop(const std::string& alias);
};

