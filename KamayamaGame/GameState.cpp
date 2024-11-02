#include "GameState.h"
#include <iostream>
#include <Windows.h>
#include "InputManager.h"


bool isPointOnRect(POINT point, RECT rect);

GameState::~GameState()
{
    //gameObjectをdelete
    for (auto& [objectName, gameObject] : gameObjects) {
        delete gameObject;
        std::wstring message = L"オブジェクト: " + objectName + L" をdeleteしました\n";
        OutputDebugString(message.c_str());
    }
    OutputDebugString(L"ゲームステートが変更されました\n");
}

const std::unordered_map<std::wstring,GameObject*>* GameState::getGameObjects() const
{
	return &gameObjects;
}

std::vector<std::wstring> GameState::getObjectOrder() const
{
    return objectOrder;
}

const GameObject* GameState::getGameObject(std::wstring objectName) const
{
    return gameObjects.at(objectName);
}

void GameState::appendObject(std::wstring objectName, LPCTSTR path, SIZE frameSize)
{
    if (gameObjects.emplace(objectName, new GameObject(path, objectName, frameSize)).second) {
        //追加成功
        objectOrder.push_back(objectName);
    }
    else {
        std::wstring message = L"ゲームオブジェクト: " + objectName + L" を追加できませんでした";
        OutputDebugString(message.c_str());
    }
}

const int GameState::numberOfObjects()const
{
    return objectOrder.size();
}

bool GameState::isClicked(std::wstring objectName, InputManager* inputManager) const
{
    if (inputManager->getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_UP) {//マウスの左ボタンが押されていない
        return false;
    }

    if (inputManager->getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_DOWN) {//左ボタンがすでに押されている
        return false;

    }
    //以下、マウスの左ボタンがクリックされた直後の処理

    POINT cursor = inputManager->getMousePosition();//カーソル座標


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
