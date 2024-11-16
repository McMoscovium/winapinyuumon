#include "HatimituMeterObject.h"

const int gap = 5;//各はちみつのすき間は5ピクセル開ける

void HatimituMeterObject::render(HDC hdc)const
{
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP oldMemBitmap = (HBITMAP)SelectObject(hdcMem, getSpriteImage());
	//2段に並べる
	//1段目
	int originX;//描画する絵の原点のX座標
	for (int i = 0; i < 10; i++) {
		if (i < getValue()) {
			//色付きのはちみつを描画
			originX = 0;
		}
		else {
			//白黒のはちみつを描画
			originX = getWidth();
		}if (TransparentBlt(
			hdc,
			getPositionX() + i * (getWidth() + ::gap),
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
			OutputDebugStringW(L"はちみつ描画しｐっぱい\n");
		}
		
	}
	SelectObject(hdcMem, oldMemBitmap);
	DeleteDC(hdcMem);
}
