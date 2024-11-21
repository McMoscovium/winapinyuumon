#pragma once

#include<Windows.h>
#include<unordered_map>

class Window;
class GameObject;
class PictureObject;

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

	//キーの状態を取得する
	KeyState getKeyState(int keyCode)const;

	//マウスの座標を取得する
	POINT getMousePosition()const;

	void setKeyState(int keyCode, KeyState keyState);

	//マウスカーソルの位置を変更する（WM_MOUSEMOVEの時に呼び出す）
	void setCursorPosition(POINT);
	//
	bool isClicked(const PictureObject& gameObject)const;

private:
	//1フレーム前のキーの状態
	std::unordered_map<int, KeyState>oldKeyStates;

	//キーの状態を格納するマップ
	std::unordered_map<int, KeyState>keyStates;

	//マウスの現在位置
	POINT mousePosition;

	//監視するキーの初期化を行う
	void initializeKeys();


};

