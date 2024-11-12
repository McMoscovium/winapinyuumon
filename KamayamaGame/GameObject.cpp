#include "GameObject.h"
//開発用
#include <iostream>
#include <string>
#include "Window.h"
#include <cmath>

GameObject::GameObject() :
	objectName(L""),
	frameSize({ 0,0 }),
	length(1)
{
	//std::wstring message = L"オブジェクト " + objectName + L" のコンストラクタが呼ばれました\n";
	//OutputDebugString(message.c_str());
}

GameObject::GameObject(LPCTSTR path, std::wstring objectName, SIZE frameSize)
	:frameSize(frameSize), objectName(objectName)
{
	loadImage(path);//hSpriteImageにビットマップハンドルを格納
	setLength(static_cast<int>(getSpriteSize().cx / frameSize.cx));//スプライトのコマ数を設定
	//std::wstring message = L"オブジェクト " + objectName + L" のコンストラクタが呼ばれました\n";
	//OutputDebugString(message.c_str());
}
GameObject::~GameObject()
{
	//std::wstring message = L"オブジェクト " + objectName + L"を破棄しました\n";
	//OutputDebugString(message.c_str());
}
void GameObject::loadImage(LPCWSTR path)
{
	setObjectImage(static_cast<HBITMAP>(LoadImage(
		NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
	)));
	if (hSpriteImage == NULL) {
		std::wstring message = L"ゲームオブジェクト: " + objectName + L" は画像をロードできませんでした\n";
		OutputDebugString(message.c_str());
	}
}

void GameObject::setObjectPosition(POINT point)
{
	position = point;
}

const POINT GameObject::getPosition() const
{
	return position;
}

void GameObject::setLength(int l) {
	length = l;
}

void GameObject::setObjectImage(HBITMAP img) {
	hSpriteImage = img;
}

SIZE GameObject::getSpriteSize() const
{
	BITMAP bmp;
	SIZE spriteSize = { -1,-1 };//hSpriteImageの縦横サイズ（ピクセル）

	if (GetObject(hSpriteImage, sizeof(BITMAP), &bmp)) {
		//getObject成功
		spriteSize.cx = bmp.bmWidth;
		spriteSize.cy = bmp.bmHeight;
	}
	else {
		//失敗
	std::wstring message = L"オブジェクト: " + objectName + L" のビットマップをGetObjectできませんでした\n";
	OutputDebugString(message.c_str());
	}
	return spriteSize;
}

const int GameObject::getCurrentFrameNumber() const
{
	return frameNumber;
}

bool GameObject::nextFrame()
{
	if (frameNumber == length - 1) {
		frameNumber = 0;
		return true;
	}
	else {
		frameNumber += 1;
		return true;
	}
}

bool GameObject::changeFrame(int frameNumber)
{
	if (frameNumber < 0 || frameNumber >= length) {
		return false;//範囲外
	}
	else {
		GameObject::frameNumber = frameNumber;
		return true;
	}
}

bool GameObject::isVisible() const
{
	return visible;
}

void GameObject::appear()
{
	visible = true;
}

void GameObject::hide()
{
	visible = false;
}

bool GameObject::isOutOfClientRect(Window* window)
{
	RECT rect = window->getClientRect();
	POINT pos = getPosition();
	if (pos.x < rect.left) {
		//左にはみ出る
		return true;
	}
	if (pos.x > rect.right) {
		//右にはみ出る
		return true;
	}
	if (pos.y < rect.top) {
		//上にはみ出る
		return true;
	}
	if (pos.y > rect.bottom) {
		//下にはみ出る
		return true;
	}
	//どこにもはみ出てない
	return false;
}

void GameObject::deleteHBITMAP()
{
	OutputDebugString(L"deleteHBITMAPが呼び出された\n");
	DeleteObject(hSpriteImage);
}

void GameObject::changeSizeRate(float r)
{
	sizeRate = r;
}

const int GameObject::getPositionX() const
{
	return position.x;
}

const int GameObject::getPositionY() const
{
	return position.y;
}

const RECT GameObject::getObjectRect() const
{
	RECT objectRect;
	objectRect.left = position.x;
	objectRect.top = position.y;
	objectRect.right = position.x + frameSize.cx;
	objectRect.bottom = position.y + frameSize.cy;
	return objectRect;
}

const int GameObject::getWidth() const
{
	return frameSize.cx;
}

const int GameObject::getHeight() const
{
	return frameSize.cy;
}

const int GameObject::getWidthOnWindow() const
{
	return static_cast<int>(std::round(
		float(getWidth()) * sizeRate
	));
}

const int GameObject::getHeightOnWindow() const
{
	return static_cast<int>(std::round(
		float(getHeight()) * sizeRate
	));
}

int GameObject::getLength() const
{
	return length;
}

const HBITMAP GameObject::getSpriteImage() const
{
	return hSpriteImage;
}

float GameObject::getSizeRate() const
{
	return sizeRate;
}

const int GameObject::originOfCurrentFrame() const
{
	return getWidth() * getCurrentFrameNumber();
}
