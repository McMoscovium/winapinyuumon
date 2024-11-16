#pragma once

#include <unordered_map>
#include <string>
#include "GameObject.h"
#include <vector>

class Game;

class IGameState
{
protected:
    Game& game;//�e��
    std::unordered_map<std::wstring, GameObject*> gameObjects = {};//GameObject�̗�i��ʉ����珇�j
    std::vector<std::wstring> objectOrder = {};//�I�u�W�F�N�g����`�揇���݂ŕ��ׂ�����
public:
    IGameState(Game& game);
    virtual ~IGameState();
    virtual void update(Game& game) = 0;
    //objectOrder�̃Q�b�^
    const std::vector<std::wstring>& getObjectOrder()const;
    //�w�肵�����O�̃Q�[���I�u�W�F�N�g�̃Q�b�^
    GameObject& getGameObject(std::wstring objectName);
    //
    GameObject* getGameObjectPtr(std::wstring objectName);
    //
    const GameObject& getConstGameObject(std::wstring objectName)const;
    //�Q�[���I�u�W�F�N�g��ǉ�
    void appendObject(std::wstring objectName, LPCTSTR path, SIZE frameSize);
    //�Q�[���I�u�W�F�N�g�𒼐ڒǉ�
    void appendObject(GameObject* object);
    //�I�u�W�F�N�g�̌�
    const unsigned int numberOfObjects()const;
    //
    void showAll();
    Game& getGame();
};

