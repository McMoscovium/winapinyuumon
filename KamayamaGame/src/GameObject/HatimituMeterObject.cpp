#include "GameObject/HatimituMeterObject.h"



void HatimituMeterObject::render(HDC hdc)const
{
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP oldMemBitmap = (HBITMAP)SelectObject(hdcMem, getSpriteImage());
	//2�i�ɕ��ׂ�
	//1�i��
	int originX;//�`�悷��G�̌��_��X���W
	for (char i = 0; i < width; i++) {
		if (i < getValue()) {
			//�g�t���F�t���̂͂��݂�`��
			originX = 0;
		}
		else if(i<getFilledValue()){
			//�g�����F�t���̂͂��݂�`��
			originX = getWidth();
		}
		else {
			//�����̂͂��݂�`��
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
			OutputDebugStringW(L"�͂��݂�1�i�ڕ`�悵�����ς�\n");
		}
	}
	//2�i��
	for (char i = 0; i < width; i++) {
		if (i+width < getValue()) {
			//�g�t���F�t���̂͂��݂�`��
			originX = 0;
		}
		else if (i+width < getFilledValue()) {
			//�g�����F�t���̂͂��݂�`��
			originX = getWidth();
		}
		else {
			//�����̂͂��݂�`��
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
			OutputDebugStringW(L"�͂��݂�1�i�ڕ`�悵�����ς�\n");
		}
	}
	SelectObject(hdcMem, oldMemBitmap);
	DeleteDC(hdcMem);
}
