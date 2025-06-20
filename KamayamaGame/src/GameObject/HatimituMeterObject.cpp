#include "GameObject/HatimituMeterObject.h"



void HatimituMeterObject::render(HDC hdc)const
{
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP oldMemBitmap = (HBITMAP)SelectObject(hdcMem, getSpriteImage());
	//2段に並べる
	//1段目
	int originX;//描画する絵の原点のX座標
	for (char i = 0; i < width; i++) {
		if (i < getValue()) {
			//枠付き色付きのはちみつを描画
			originX = 0;
		}
		else if(i<getFilledValue()){
			//枠無し色付きのはちみつを描画
			originX = getWidth();
		}
		else {
			//白黒のはちみつを描画
			originX = 2 * getWidth();
		}
		if (TransparentBlt(
			hdc,
			getPositionX() + i * (getWidth() + gap),
			getPositionY(),
			getWidthOnWindow(),
			getHeightOnWindow(),
			hdcMem,
			originX,
			0,
			getWidth(),
			getHeight(),
			RGB(255, 0, 255)
		)) {
		}
		else {
			OutputDebugStringW(L"はちみつ1段目描画しｐっぱい\n");
		}
	}
	//2段目
	for (char i = 0; i < width; i++) {
		if (i+width < getValue()) {
			//枠付き色付きのはちみつを描画
			originX = 0;
		}
		else if (i+width < getFilledValue()) {
			//枠無し色付きのはちみつを描画
			originX = getWidth();
		}
		else {
			//白黒のはちみつを描画
			originX = 2 * getWidth();
		}
		if (TransparentBlt(
			hdc,
			getPositionX() + i * (getWidth() + gap),
			getPositionY()+getHeight(),
			getWidthOnWindow(),
			getHeightOnWindow(),
			hdcMem,
			originX,
			0,
			getWidth(),
			getHeight(),
			RGB(255, 0, 255)
		)) {
		}
		else {
			OutputDebugStringW(L"はちみつ1段目描画しｐっぱい\n");
		}
	}
	SelectObject(hdcMem, oldMemBitmap);
	DeleteDC(hdcMem);
}
