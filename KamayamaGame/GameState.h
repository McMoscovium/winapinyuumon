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
	std::unordered_map<std::string, GameObject*> gameObjects;//GameObject�̗�i��ʉ����珇�j
	std::vector<std::string> objectOrder;//�I�u�W�F�N�g����`�揇���݂ŕ��ׂ�����
private:
	
public:
	virtual ~GameState() = default;

	//��ԍX�V
	virtual void update(Game* game,InputManager* inputManager) = 0;

	//�Q�[���I�u�W�F�N�g���X�g�̃Q�b�^
	virtual const std::unordered_map<std::string, GameObject*>* getGameObjects()const;

	//objectOrder�̃Q�b�^
	std::vector<std::string> getObjectOrder()const;

	//�w�肵�����O�̃Q�[���I�u�W�F�N�g�̃Q�b�^
	virtual const GameObject* getGameObject(std::string objectName)const;

	//�Q�[���I�u�W�F�N�g��ǉ�
	virtual void appendObject(std::string objectName, LPCTSTR path, SIZE frameSize);

	//�I�u�W�F�N�g�̌�
	virtual const int numberOfObjects()const;
private:
};