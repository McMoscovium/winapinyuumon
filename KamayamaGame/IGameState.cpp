#include "IGameState.h"

IGameState::IGameState(Game& game):
    game(game)
{
}

IGameState::~IGameState()
{
    for (auto& [key, obj] : gameObjects) {
        obj->deleteHBITMAP();
        delete obj;
        obj = nullptr;
    }
}

const std::vector<std::wstring>& IGameState::getObjectOrder() const
{
    return objectOrder;
}

GameObject& IGameState::getGameObject(std::wstring objectName)
{
    return *gameObjects.at(objectName);
}

GameObject* IGameState::getGameObjectPtr(std::wstring objectName)
{
    return gameObjects.at(objectName);
}

const GameObject& IGameState::getConstGameObject(std::wstring objectName)const
{
    return *gameObjects.at(objectName);
}

void IGameState::appendObject(std::wstring objectName, LPCTSTR path, SIZE frameSize)
{
    GameObject* obj =new GameObject(path, objectName, frameSize);
    if (gameObjects.emplace(objectName, std::move(obj)).second) {
        OutputDebugString(L"PICTURE_TITLE �f�X�g���N�g�H\n");
        //�ǉ�����
        objectOrder.push_back(objectName);
    }
    else {
        std::wstring message = L"�Q�[���I�u�W�F�N�g: " + objectName + L" ��ǉ��ł��܂���ł���";
        OutputDebugString(message.c_str());
    }
    
}

const unsigned int IGameState::numberOfObjects() const
{
    return (unsigned int)objectOrder.size();
}

void IGameState::showAll()
{
    for (auto& [key, obj] : gameObjects) {
        obj->appear();
    }
}

Game& IGameState::getGame()
{
    return game;
}
