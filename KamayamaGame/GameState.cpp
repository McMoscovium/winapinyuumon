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
        //�ǉ�����
        objectOrder.push_back(objectName);
    }
    else {
        //�ǉ����s
        std::cout << "�Q�[���I�u�W�F�N�g��: " << objectName << " ��ǉ��ł��܂���ł���" << std::endl;
    }
}

const int GameState::numberOfObjects()const
{
    return objectOrder.size();
}