#pragma once

#include "GameObject.h"

#include "BatBoundingBox.h"
#include <memory>

#include <Windows.h>

class Vector2D;
class InputManager;
class Ball;
class PlayingState;

class Batter:
	public GameObject
{
public:
	Batter(LPCTSTR path, std::wstring objectName, SIZE frameSize, PlayingState& context);
	//スイング中のヒッティング判定
	bool isHit(Ball);
	//inputManagerの情報に従ってバッターの位置更新
	void updateBatterPos(const InputManager& inputManager);
	void updateSwingAnimation(const InputManager& inputManager);
	void updateBatBoundingBox(int currentBatterFrame);
	//animateBatter()に使う変数
	bool releasedLeftButtonUntilSwingEnded = false;
	//バッターの移動スピード
	int moveSpeed = 4;
	//バッターが移動可能な範囲
	const RECT batterBox;
	//
	POINT nextBatterPos(POINT position, Vector2D movement);
	
	
	
	//ヒッティングカーソルの位置
	POINT cursorPos()const;
	//バッティングカーソルのX座標
	LONG cursorX();
	//バッティングカーソルのY座標
	LONG cursorY();
private:
	PlayingState& context;
};