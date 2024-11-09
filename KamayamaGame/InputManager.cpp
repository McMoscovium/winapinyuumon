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
	//初期化処理
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
			&& (getKeyState(keyCode) == KeyState::KEY_PRESSED)) {//押されたまま
			setKeyState(keyCode, KeyState::KEY_DOWN);
		}

		if ((oldKeyState == KeyState::KEY_RELEASED)
			&& (getKeyState(keyCode) == KeyState::KEY_RELEASED)) {//離されたまま
			setKeyState(keyCode, KeyState::KEY_UP);
		}
	}


	//最後に、oldKeyStatesに状態をコピー
	oldKeyStates = keyStates;
}

bool InputManager::isKeyPressed(int keyCode) {
	return keyStates[keyCode] == InputManager::KeyState::KEY_PRESSED;
}

bool InputManager::isClicked(const GameObject& object) const
{
	if (!object.isVisible()) {//オブジェクトが表示されていない
		return false;
	}

	//以下、オブジェクトが表示されている

	if (getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_UP) {//マウスの左ボタンが押されていない
		return false;
	}

	//以下マウスの左ボタンが押されている

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

