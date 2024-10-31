#include "GameState.h"
#include <iostream>
#include <Windows.h>

const std::unordered_map<std::string,GameObject*>* GameState::getGameObjects() const
{
	return &gameObjects;
}

std::vector<std::string> GameState::getObjectOrder() const
{
    return objectOrder;
}

const GameObject* GameState::getGameObject(std::string objectName) const
{
    return gameObjects.at(objectName);
}

void GameState::appendObject(std::string objectName, LPCTSTR path, SIZE frameSize)
{
    if (gameObjects.emplace(objectName, new GameObject(path, objectName, frameSize)).second) {
        //追加成功
        objectOrder.push_back(objectName);
    }
    else {
        //追加失敗
        std::cout << "ゲームオブジェクト名: " << objectName << " を追加できませんでした" << std::endl;
    }
}

const int GameState::numberOfObjects()const
{
    return objectOrder.size();
}