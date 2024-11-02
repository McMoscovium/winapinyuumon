#pragma once

#include "GameObject.h"
#include <string>
#include <unordered_map>
#include <vector>

class Game;
class InputManager;

class GameState
{
public:

protected:
	std::unordered_map<std::wstring, GameObject*> gameObjects;//GameObjectの列（画面奥から順）
	std::vector<std::wstring> objectOrder;//オブジェクト名を描画順込みで並べたもの
private:
	
public:
	virtual ~GameState();

	//状態更新
	virtual void update(Game* game,InputManager* inputManager) = 0;

	//ゲームオブジェクトリストのゲッタ
	virtual const std::unordered_map<std::wstring, GameObject*>* getGameObjects()const;

	//objectOrderのゲッタ
	std::vector<std::wstring> getObjectOrder()const;

	//指定した名前のゲームオブジェクトのゲッタ
	virtual const GameObject* getGameObject(std::wstring objectName)const;

	//ゲームオブジェクトを追加
	virtual void appendObject(std::wstring objectName, LPCTSTR path, SIZE frameSize);

	//オブジェクトの個数
	virtual const int numberOfObjects()const;

	virtual bool isClicked(std::wstring objectName, InputManager* inputManager)const;
private:
};