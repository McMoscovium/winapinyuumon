#include "HatimituMeterObject.h"

const int gap = 5;//�e�͂��݂̂����Ԃ�5�s�N�Z���J����

void HatimituMeterObject::render(HDC hdc)const
{
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP oldMemBitmap = (HBITMAP)SelectObject(hdcMem, getSpriteImage());
	//2�i�ɕ��ׂ�
	//1�i��
	int originX;//�`�悷��G�̌��_��X���W
	for (int i = 0; i < 10; i++) {
		if (i < getValue()) {
			//�F�t���̂͂��݂�`��
			originX = 0;
		}
		else {
			//�����̂͂��݂�`��
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
			OutputDebugStringW(L"�͂��݂`�悵�����ς�\n");
		}
		
	}
	SelectObject(hdcMem, oldMemBitmap);
	DeleteDC(hdcMem);
}
