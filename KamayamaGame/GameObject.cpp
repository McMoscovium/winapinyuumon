#include "GameObject.h"
//開発用
#include <iostream>
#include <string>

GameObject::GameObject(LPCTSTR path, std::string objectName, SIZE frameSize)
	:frameSize(frameSize), objectName(objectName)
{
	loadImage(path);//hSpriteImageにビットマップハンドルを格納
	setLength(static_cast<int>(getSpriteSize().cx / frameSize.cx));//スプライトのコマ数を設定
	//以下テスト用
	std::cout << objectName << " のlength: " << length << std::endl;
}
void GameObject::loadImage(LPCWSTR path)
{
	setObjectImage(static_cast<HBITMAP>(LoadImage(
		NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
	)));
	if (hSpriteImage == NULL) {
		//読み込み失敗
		std::cout << "ゲームオブジェクト " << objectName << " は画像をロードできませんでした" << std::endl;
	}
}

void GameObject::setObjectPosition(POINT point)
{
	position = point;
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
		std::cout << "オブジェクト " << objectName << "のビットマップをGetObjectできませんでした。" << std::endl;
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
