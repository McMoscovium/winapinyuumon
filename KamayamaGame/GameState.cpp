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

bool GameState::isClicked(std::string objectName, InputManager* inputManager) const
{
    if (inputManager->getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_UP) {//�}�E�X�̍��{�^����������Ă��Ȃ�
        return false;
    }
    //�ȉ��A�}�E�X�̍��{�^����������Ă���

    POINT cursor = inputManager->getMousePosition();//�J�[�\�����W

    int x = cursor.x, y = cursor.y;
    std::wstring message = L"x = " + std::to_wstring(x) + L", y = " + std::to_wstring(y) + L" ���N���b�N���ꂽ\n";
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
