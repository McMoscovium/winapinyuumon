#include "InputManager.h"
#include "Window.h"
#include <string>
#include "GameObject.h"

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

InputManager::InputManager() :mousePosition{ 0,0 }
{
	//����������
	keyStates.clear();
	initializeKeys();
}

InputManager::~InputManager()
{
}

void InputManager::initializeKeys() {//@TODO
	keyStates.insert({ VK_LBUTTON,InputManager::KeyState::KEY_UP });
}

void InputManager::update()
{
	for (auto& [keyCode, oldKeyState] : oldKeyStates) {
		//
		if ((oldKeyState == KeyState::KEY_PRESSED)
			&& (getKeyState(keyCode) == KeyState::KEY_PRESSED)) {//�����ꂽ�܂�
			setKeyState(keyCode, KeyState::KEY_DOWN);
		}

		if ((oldKeyState == KeyState::KEY_RELEASED)
			&& (getKeyState(keyCode) == KeyState::KEY_RELEASED)) {//�����ꂽ�܂�
			setKeyState(keyCode, KeyState::KEY_UP);
		}
	}


	//�Ō�ɁAoldKeyStates�ɏ�Ԃ��R�s�[
	oldKeyStates = keyStates;
}

bool InputManager::isKeyPressed(int keyCode) {
	return keyStates[keyCode] == InputManager::KeyState::KEY_PRESSED;
}

bool InputManager::isClicked(const GameObject& object) const
{
	if (!object.isVisible()) {//�I�u�W�F�N�g���\������Ă��Ȃ�
		return false;
	}

	//�ȉ��A�I�u�W�F�N�g���\������Ă���

	if (getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_UP) {//�}�E�X�̍��{�^����������Ă��Ȃ�
		return false;
	}

	//�ȉ��}�E�X�̍��{�^����������Ă���

	RECT objectRect = object.getObjectRect();
	if (isPointOnRect(getMousePosition(), objectRect)) {
		return true;
	}
	else {
		return false;
	}
}


InputManager::KeyState InputManager::getKeyState(int keyCode)const
{
	return keyStates.count(keyCode) ? keyStates.at(keyCode) : InputManager::KeyState::KEY_UP;
}

POINT InputManager::getMousePosition()const {
	return mousePosition;
}

void InputManager::setKeyState(int keyCode, KeyState keyState)
{
	keyStates[keyCode] = keyState;
}

void InputManager::setCursorPosition(POINT point)
{
	mousePosition = point;
}

