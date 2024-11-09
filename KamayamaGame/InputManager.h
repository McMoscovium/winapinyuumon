#pragma once

#include<Windows.h>
#include<unordered_map>
#include <memory>

class Window;
class GameObject;

class InputManager
{
public:
	//キーの状態を表す列挙型
	enum class KeyState {
		KEY_UP,//キーは押されていないまま
		KEY_DOWN,//キーは押されたまま
		KEY_PRESSED,//キーがちょうど押された
		KEY_RELEASED//キーがちょうど離された
	};

	InputManager();
	~InputManager();

	//キーの状態を更新する
	void update();

	//指定したキーが押されているか確認する
	bool isKeyPressed(int keyCode);
	//指定したゲームオブジェクトがクリックされているか確認する
	bool isClicked(const GameObject& object)const;
	//指定したキーの状態のゲッター
	KeyState getKeyState(int keyCode)const;
	//マウスの座標のゲッター
	POINT getMousePosition()const;
	//
	void setKeyState(int keyCode, KeyState keyState);
	//マウスカーソルの位置を変更する（WM_MOUSEMOVEの時に呼び出す）
	void setCursorPosition(POINT);

private:
	//1フレーム前のキーの状態
	std::unordered_map<int, KeyState>oldKeyStates;

	//現在のキーの状態を格納するマップ
	std::unordered_map<int, KeyState>keyStates;

	//マウスの現在位置
	POINT mousePosition;

	//監視するキーの初期化を行う
	void initializeKeys();
};