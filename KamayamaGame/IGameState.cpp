#include "IGameState.h"

IGameState::IGameState(Game& game):
    game(game)
{
}

const std::vector<std::wstring>& IGameState::getObjectOrder() const
{
    return objectOrder;
}

GameObject& IGameState::getGameObject(std::wstring objectName)
{
    return gameObjects.at(objectName);
}

const GameObject& IGameState::getConstGameObject(std::wstring objectName)const
{
    return gameObjects.at(objectName);
}

void IGameState::appendObject(std::wstring objectName, LPCTSTR path, SIZE frameSize)
{
    if (gameObjects.emplace(objectName, GameObject(path, objectName, frameSize)).second) {
        //追加成功
        objectOrder.push_back(objectName);
    }
    else {
        std::wstring message = L"ゲームオブジェクト: " + objectName + L" を追加できませんでした";
        OutputDebugString(message.c_str());
    }
}

const int IGameState::numberOfObjects() const
{
    return objectOrder.size();
}
