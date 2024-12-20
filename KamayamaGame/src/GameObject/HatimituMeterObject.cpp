#include "GameObject/HatimituMeterObject.h"



void HatimituMeterObject::render(HDC hdc)const
{
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP oldMemBitmap = (HBITMAP)SelectObject(hdcMem, getSpriteImage());
	//2’i‚É•À‚×‚é
	//1’i–Ú
	int originX;//•`‰æ‚·‚éŠG‚ÌŒ´“_‚ÌXÀ•W
	for (char i = 0; i < width; i++) {
		if (i < getValue()) {
			//˜g•t‚«F•t‚«‚Ì‚Í‚¿‚İ‚Â‚ğ•`‰æ
			originX = 0;
		}
		else if(i<getFilledValue()){
			//˜g–³‚µF•t‚«‚Ì‚Í‚¿‚İ‚Â‚ğ•`‰æ
			originX = getWidth();
		}
		else {
			//”’•‚Ì‚Í‚¿‚İ‚Â‚ğ•`‰æ
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
			OutputDebugStringW(L"‚Í‚¿‚İ‚Â1’i–Ú•`‰æ‚µ‚‚Á‚Ï‚¢\n");
		}
	}
	//2’i–Ú
	for (char i = 0; i < width; i++) {
		if (i+width < getValue()) {
			//˜g•t‚«F•t‚«‚Ì‚Í‚¿‚İ‚Â‚ğ•`‰æ
			originX = 0;
		}
		else if (i+width < getFilledValue()) {
			//˜g–³‚µF•t‚«‚Ì‚Í‚¿‚İ‚Â‚ğ•`‰æ
			originX = getWidth();
		}
		else {
			//”’•‚Ì‚Í‚¿‚İ‚Â‚ğ•`‰æ
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
			OutputDebugStringW(L"‚Í‚¿‚İ‚Â1’i–Ú•`‰æ‚µ‚‚Á‚Ï‚¢\n");
		}
	}
	SelectObject(hdcMem, oldMemBitmap);
	DeleteDC(hdcMem);
}
