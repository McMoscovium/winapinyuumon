#include "Game/InputManager.h"

#include "GameObject/GameObject.h"
#include "Game/Window.h"
#include <string>

#include "GameObject/PictureObject.h"

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
	keyStates.insert({ 0x4D,KeyState::KEY_UP });//0x4d=「M」
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

bool InputManager::isClicked(const PictureObject& gameObject)const
{
	if (!gameObject.isVisible()) {//オブジェクトが見えない
		return false;
	}
	if (getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_UP) {
		//マウスの左ボタンが離されたまま
		return false;
	}
	if (getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_DOWN) {
		//左ボタンがすでに押されている
		return false;
	}
	if (getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_PRESSED) {
		//左ボタンがちょうど押された
		return false;
	}

	//左ボタンがちょうど離された
	POINT cursor = getMousePosition();

	RECT rect = gameObject.getObjectRect();

	if (isPointOnRect(cursor, rect)) {
		return true;
	}
	else {
		return false;
	}
}

