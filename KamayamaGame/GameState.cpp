#include "GameState.h"
#include <iostream>
#include <Windows.h>
#include "InputManager.h"


bool isPointOnRect(POINT point, RECT rect);

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

bool GameState::isClicked(std::string objectName, InputManager* inputManager) const
{
    if (inputManager->getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_UP) {//マウスの左ボタンが押されていない
        return false;
    }
    //以下、マウスの左ボタンが押されている

    POINT cursor = inputManager->getMousePosition();//カーソル座標

    int x = cursor.x, y = cursor.y;
    std::wstring message = L"x = " + std::to_wstring(x) + L", y = " + std::to_wstring(y) + L" がクリックされた\n";
    OutputDebugString(message.c_str());


    GameObject* object = gameObjects.at(objectName);
    RECT objectRect = object->getObjectRect();
    if (isPointOnRect(cursor, objectRect)) {
        return true;
    }
    else {
        return false;
    }
}

bool isPointOnRect(POINT point, RECT rect)
{
    if (point.x <= rect.right &&
        point.x >= rect.left &&
        point.y <= rect.bottom &&
        point.y >= rect.top
        ) {
        return true;
    }
    else {
        return false;
    }
}
