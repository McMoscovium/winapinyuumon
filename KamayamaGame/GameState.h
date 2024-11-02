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
	std::unordered_map<std::wstring, GameObject*> gameObjects;//GameObject�̗�i��ʉ����珇�j
	std::vector<std::wstring> objectOrder;//�I�u�W�F�N�g����`�揇���݂ŕ��ׂ�����
private:
	
public:
	virtual ~GameState();

	//��ԍX�V
	virtual void update(Game* game,InputManager* inputManager) = 0;

	//�Q�[���I�u�W�F�N�g���X�g�̃Q�b�^
	virtual const std::unordered_map<std::wstring, GameObject*>* getGameObjects()const;

	//objectOrder�̃Q�b�^
	std::vector<std::wstring> getObjectOrder()const;

	//�w�肵�����O�̃Q�[���I�u�W�F�N�g�̃Q�b�^
	virtual const GameObject* getGameObject(std::wstring objectName)const;

	//�Q�[���I�u�W�F�N�g��ǉ�
	virtual void appendObject(std::wstring objectName, LPCTSTR path, SIZE frameSize);

	//�I�u�W�F�N�g�̌�
	virtual const int numberOfObjects()const;

	virtual bool isClicked(std::wstring objectName, InputManager* inputManager)const;
private:
};