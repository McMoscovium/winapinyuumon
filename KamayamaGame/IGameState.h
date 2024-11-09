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
    //GameObject�̗�i��ʉ����珇�j
    std::unordered_map<std::wstring, GameObject> gameObjects;
	//�I�u�W�F�N�g����`�揇���݂ŕ��ׂ�����
	std::vector<std::wstring> objectOrder;
	//�e��
	Game& game;
public:
	IGameState(Game& game);
	const Game& getConstGame()const;
	Game& getGame();
    virtual ~IGameState() = default;
    virtual void update() = 0;
	//�Q�[���I�u�W�F�N�g��ǉ�
	void appendObjectFromFile(std::wstring objectName, LPCTSTR path, SIZE frameSize) {
		if (gameObjects.emplace(objectName, GameObject(path, objectName, frameSize)).second) {
			//�ǉ�����
			objectOrder.push_back(objectName);
		}
		else {
			std::wstring message = L"�Q�[���I�u�W�F�N�g: " + objectName + L" ��ǉ��ł��܂���ł���";
			OutputDebugString(message.c_str());
		}
	}
	void appendObject(std::wstring objectName, GameObject& gameObject) {
		if (gameObjects.emplace(objectName, gameObject).second) {
			//�ǉ�����
			objectOrder.push_back(objectName);
		}
		else {
			//�ǉ����s
			std::wstring message = L"�I�u�W�F�N�g: " + objectName + L" ��appendObject�ł��܂���ł���\n";
			OutputDebugString(message.c_str());
		}
	}
	//�w�肵�����O�̃Q�[���I�u�W�F�N�g�̃Q�b�^
	GameObject& getGameObject(std::wstring objectName) {
		return gameObjects.at(objectName);
	}
	//objectOrder�̃Q�b�^
	std::vector<std::wstring> getObjectOrder()const {
		return objectOrder;
	}
	//�I�u�W�F�N�g�̌�
	virtual const size_t numberOfObjects()const {
		return objectOrder.size();
	}
};