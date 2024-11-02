#include "GameState.h"
#include <iostream>
#include <Windows.h>
#include "InputManager.h"


bool isPointOnRect(POINT point, RECT rect);

GameState::~GameState()
{
    //gameObject��delete
    for (auto& [objectName, gameObject] : gameObjects) {
        delete gameObject;
        std::wstring message = L"�I�u�W�F�N�g: " + objectName + L" ��delete���܂���\n";
        OutputDebugString(message.c_str());
    }
    OutputDebugString(L"�Q�[���X�e�[�g���ύX����܂���\n");
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
        //�ǉ�����
        objectOrder.push_back(objectName);
    }
    else {
        std::wstring message = L"�Q�[���I�u�W�F�N�g: " + objectName + L" ��ǉ��ł��܂���ł���";
        OutputDebugString(message.c_str());
    }
}

const int GameState::numberOfObjects()const
{
    return objectOrder.size();
}

bool GameState::isClicked(std::wstring objectName, InputManager* inputManager) const
{
    if (inputManager->getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_UP) {//�}�E�X�̍��{�^����������Ă��Ȃ�
        return false;
    }

    if (inputManager->getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_DOWN) {//���{�^�������łɉ�����Ă���
        return false;

    }
    //�ȉ��A�}�E�X�̍��{�^�����N���b�N���ꂽ����̏���

    POINT cursor = inputManager->getMousePosition();//�J�[�\�����W


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
