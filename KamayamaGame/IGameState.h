#pragma once

#include <Windows.h>
#include <string>
#include "GameObject.h"
#include <vector>
#include <unordered_map>

class Game;

class IGameState
{
protected:
    //GameObjectの列（画面奥から順）
    std::unordered_map<std::wstring, GameObject> gameObjects;
	//オブジェクト名を描画順込みで並べたもの
	std::vector<std::wstring> objectOrder;
	//親玉
	Game& game;
public:
	IGameState(Game& game);
	const Game& getConstGame()const;
	Game& getGame();
    virtual ~IGameState() = default;
    virtual void update() = 0;
	//ゲームオブジェクトを追加
	void appendObjectFromFile(std::wstring objectName, LPCTSTR path, SIZE frameSize) {
		if (gameObjects.emplace(objectName, GameObject(path, objectName, frameSize)).second) {
			//追加成功
			objectOrder.push_back(objectName);
		}
		else {
			std::wstring message = L"ゲームオブジェクト: " + objectName + L" を追加できませんでした";
			OutputDebugString(message.c_str());
		}
	}
	void appendObject(std::wstring objectName, GameObject& gameObject) {
		if (gameObjects.emplace(objectName, gameObject).second) {
			//追加成功
			objectOrder.push_back(objectName);
		}
		else {
			//追加失敗
			std::wstring message = L"オブジェクト: " + objectName + L" はappendObjectできませんでした\n";
			OutputDebugString(message.c_str());
		}
	}
	//指定した名前のゲームオブジェクトのゲッタ
	GameObject& getGameObject(std::wstring objectName) {
		return gameObjects.at(objectName);
	}
	//objectOrderのゲッタ
	std::vector<std::wstring> getObjectOrder()const {
		return objectOrder;
	}
	//オブジェクトの個数
	virtual const size_t numberOfObjects()const {
		return objectOrder.size();
	}
};