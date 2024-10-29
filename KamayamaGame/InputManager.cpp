#include "InputManager.h"

InputManager::InputManager() :mousePosition{ 0,0 }
{
	//初期化処理
	keyStates.clear();
}

InputManager::~InputManager()
{
}

void InputManager::initializeKeys() {//@TODO
	VK_LBUTTON;
}


void InputManager::update()
{
	//ｷｰﾎﾞｰﾄﾞの状態を更新する
	for (auto& [keyCode, state] : keyStates) {
		//現在のキー状態を確認
		if (GetAsyncKeyState(keyCode) & 0x8000) {
			//キーが押されている場合
			if (state == InputManager::KeyState::KEY_UP) {
				keyStates[keyCode] = InputManager::KeyState::KEY_PRESSED;
			}
			else {
				keyStates[keyCode] = InputManager::KeyState::KEY_DOWN;
			}
		}
		else {
			keyStates[keyCode] = InputManager::KeyState::KEY_UP;
		}
	}

	//マウスの位置を更新
	GetCursorPos(&mousePosition);
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
