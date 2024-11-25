#include "PictureObject.h"

#include "Window.h"
#include <cmath>

void PictureObject::setLength(int l)
{
	length = l;
}

void PictureObject::setObjectImage(HBITMAP img)
{
	hSpriteImage = img;
}

bool PictureObject::loadImage(LPCWSTR path)
{
	setObjectImage(static_cast<HBITMAP>(LoadImage(
		NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
	)));
	if (hSpriteImage == NULL) {
		//よみこみしっぱい
		return false;
	}
	return true;
}

PictureObject::PictureObject(const std::string& objectName, const LPCTSTR& path, const SIZE& frameSize) :
	GameObject(objectName),
	frameSize(frameSize)
{
	if (!loadImage(path)) {
		std::string message = "オブジェクト: " + objectName + " はロードできませんでした\n";
		OutputDebugStringA(message.c_str());
		return;
	}
	setLength(static_cast<int>(getSpriteSize().cx / frameSize.cx));//スプライトのコマ数を設定
}

PictureObject::~PictureObject()
{
	DeleteObject(hSpriteImage);
}

int PictureObject::getLength() const
{
	return length;
}

const HBITMAP PictureObject::getSpriteImage() const
{
	return hSpriteImage;
}

const int PictureObject::originOfCurrentFrame() const
{
	return getWidth() * getCurrentFrameNumber();
}

SIZE PictureObject::getSpriteSize() const
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
		std::string message = "オブジェクト: " + objectName + " のビットマップをGetObjectできませんでした\n";
		OutputDebugStringA(message.c_str());
	}
	return spriteSize;
}

const int PictureObject::getCurrentFrameNumber() const
{
	return frameNumber;
}

bool PictureObject::nextFrame()
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

bool PictureObject::changeFrame(int frameNumber)
{
	if (frameNumber < 0 || frameNumber >= length) {
		OutputDebugString(L"PicturObject::changeFrame(): 範囲外のフレーム番号が入力されました\n");
		return false;//範囲外
	}
	else {
		PictureObject::frameNumber = frameNumber;
		return true;
	}
}

void PictureObject::deleteHBITMAP()
{
	DeleteObject(hSpriteImage);
}

void PictureObject::render(HDC hdc) const
{
	HDC hdcMem = CreateCompatibleDC(hdc);//スプライトシートに紐付けるHDC
	HBITMAP oldMemBitmap = (HBITMAP)SelectObject(hdcMem, getSpriteImage());
	//透過色を考慮してHDCの選択するデバイスに描画
	if (TransparentBlt(
		hdc,
		getPositionX(),
		getPositionY(),
		getWidthOnWindow(),
		getHeightOnWindow(),
		hdcMem,
		originOfCurrentFrame(),
		0,
		getWidth(),
		getHeight(),
		RGB(255, 0, 255))
		) {
		//描画せいこう
	}
	else {
		//描画失敗
		OutputDebugString(L"仮想画面に描画失敗\n");
	}
	SelectObject(hdcMem, oldMemBitmap);
	DeleteDC(hdcMem);//HDC解放
}

const RECT PictureObject::getObjectRect() const
{
	RECT objectRect;
	objectRect.left = position.x;
	objectRect.top = position.y;
	objectRect.right = position.x + frameSize.cx;
	objectRect.bottom = position.y + frameSize.cy;
	return objectRect;
}

const int PictureObject::getWidth() const
{
	return frameSize.cx;
}

const int PictureObject::getHeight() const
{
	return frameSize.cy;
}

const int PictureObject::getWidthOnWindow() const
{
	return static_cast<int>(std::round(
		float(getWidth()) * sizeRate
	));
}

const int PictureObject::getHeightOnWindow() const
{
	return static_cast<int>(std::round(
		float(getHeight()) * sizeRate
	));
}

bool PictureObject::isIntersectsWithClientRect(Window* window)
{
	RECT objRect = getObjectRect();
	RECT clientRect = window->getClientRect();
	if (objRect.right < clientRect.left) {
		//左に外れる
		return false;
	}
	if (objRect.bottom < clientRect.top) {
		//上に外れる
		return false;
	}
	if (objRect.left > clientRect.right) {
		//右に外れる
		return false;
	}
	if (objRect.top > clientRect.bottom) {
		//下に外れる
		return false;
	}
	return true;
}
