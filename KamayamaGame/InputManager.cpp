#include "InputManager.h"
#include "Window.h"

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
	//���ް�ނ̏�Ԃ��X�V����
	for (auto& [keyCode, state] : keyStates) {
		//���݂̃L�[��Ԃ��m�F
		if (GetAsyncKeyState(keyCode) & 0x8000) {
			//�L�[��������Ă���ꍇ
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
	//�}�E�X�̈ʒu���X�V
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

void InputManager::setKeyState(int keyCode, KeyState keyState)
{
	keyStates[keyCode] = keyState;
}

void InputManager::setCursorPosition(POINT point)
{
	mousePosition = point;
}

