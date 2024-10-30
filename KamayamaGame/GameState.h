#pragma once

#include <unordered_map>
#include "GameObject.h"
#include <string>
#include <vector>

class Game;
class InputManager;

class GameState
{
public:
	virtual ~GameState() = default;
	virtual void update(Game* game,InputManager* inputManager) = 0;
	virtual const std::unordered_map<std::wstring, GameObject*>* getGameObjects()const = 0;

private:
	std::vector<std::wstring> objectNames;
	std::unordered_map<std::wstring, GameObject*> gameObjects;//GameObject‚Æ‚»‚Ì–¼‘O‚ÌƒyƒA
};