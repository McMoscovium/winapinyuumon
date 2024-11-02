#include "GameObject.h"
//開発用
#include <iostream>
#include <string>

GameObject::GameObject(LPCTSTR path, std::wstring objectName, SIZE frameSize)
	:frameSize(frameSize), objectName(objectName)
{
	loadImage(path);//hSpriteImageにビットマップハンドルを格納
	setLength(static_cast<int>(getSpriteSize().cx / frameSize.cx));//スプライトのコマ数を設定
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

const HBITMAP GameObject::getSpriteImage() const
{
	return hSpriteImage;
}

const int GameObject::originOfCurrentFrame() const
{
	return getWidth() * getCurrentFrameNumber();
}
