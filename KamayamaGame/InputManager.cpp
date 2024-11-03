#include "InputManager.h"
#include "Window.h"
#include <string>

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

	std::wstring message = L"";

	switch (getKeyState(VK_LBUTTON)) {
	case KeyState::KEY_UP:
		message += L"KEY_UP";
		break;
	case KeyState::KEY_DOWN:
		message += L"KEY_DOWN";
		break;
	case KeyState::KEY_PRESSED:
		message += L"KEY_PRESSED";
		break;
	case KeyState::KEY_RELEASED:
		message += L"KEY_RELEASED";
		break;
	}
	message += L"\n";
	OutputDebugString(message.c_str());

	//最後に、oldKeyStatesに状態をコピー
	oldKeyStates = keyStates;
}

bool InputManager::isKeyPressed(int keyCode) {
	return keyStates[keyCode] == InputManager::KeyState::KEY_PRESSED;
}

InputManager::KeyState InputManager::getKeyState(int keyCode)
{
	return keyStates.count(keyCode) ? keyStates[keyCode] : InputManager::KeyState::KEY_UP;
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

