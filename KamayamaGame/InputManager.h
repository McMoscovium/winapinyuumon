#pragma once

#include<Windows.h>
#include<unordered_map>



class InputManager
{
public:
	//キーの状態を表す列挙型
	enum class KeyState {
		KEY_UP,
		KEY_DOWN,
		KEY_PRESSED
	};

	InputManager();
	~InputManager();

	//キーの状態を更新する
	void update();

	//指定したキーが押されているか確認する
	bool isKeyPressed(int keyCode);

	//キーの状態を取得する
	KeyState getKeyState(int keyCode);

	POINT getMousePosition()const;

private:
	//キーの状態を格納するマップ
	std::unordered_map<int, KeyState>keyStates;

	//マウスの現在位置
	POINT mousePosition;

	//監視するキーの初期化
	void initializeKeys();
};

