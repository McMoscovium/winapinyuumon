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
		//��݂��݂����ς�
		return false;
	}
	return true;
}

PictureObject::PictureObject(const std::string& objectName, const LPCTSTR& path, const SIZE& frameSize) :
	GameObject(objectName),
	frameSize(frameSize)
{
	if (!loadImage(path)) {
		std::string message = "�I�u�W�F�N�g: " + objectName + " �̓��[�h�ł��܂���ł���\n";
		OutputDebugStringA(message.c_str());
		return;
	}
	setLength(static_cast<int>(getSpriteSize().cx / frameSize.cx));//�X�v���C�g�̃R�}����ݒ�
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
	SIZE spriteSize = { -1,-1 };//hSpriteImage�̏c���T�C�Y�i�s�N�Z���j

	if (GetObject(hSpriteImage, sizeof(BITMAP), &bmp)) {
		//getObject����
		spriteSize.cx = bmp.bmWidth;
		spriteSize.cy = bmp.bmHeight;
	}
	else {
		//���s
		std::string message = "�I�u�W�F�N�g: " + objectName + " �̃r�b�g�}�b�v��GetObject�ł��܂���ł���\n";
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
		OutputDebugString(L"PicturObject::changeFrame(): �͈͊O�̃t���[���ԍ������͂���܂���\n");
		return false;//�͈͊O
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
	HDC hdcMem = CreateCompatibleDC(hdc);//�X�v���C�g�V�[�g�ɕR�t����HDC
	HBITMAP oldMemBitmap = (HBITMAP)SelectObject(hdcMem, getSpriteImage());
	//���ߐF���l������HDC�̑I������f�o�C�X�ɕ`��
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
		//�`�悹������
	}
	else {
		//�`�掸�s
		OutputDebugString(L"���z��ʂɕ`�掸�s\n");
	}
	SelectObject(hdcMem, oldMemBitmap);
	DeleteDC(hdcMem);//HDC���
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
		//���ɊO���
		return false;
	}
	if (objRect.bottom < clientRect.top) {
		//��ɊO���
		return false;
	}
	if (objRect.left > clientRect.right) {
		//�E�ɊO���
		return false;
	}
	if (objRect.top > clientRect.bottom) {
		//���ɊO���
		return false;
	}
	return true;
}
