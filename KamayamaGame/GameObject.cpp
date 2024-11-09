#include "GameObject.h"
//�J���p
#include <iostream>
#include <string>

GameObject::GameObject(LPCTSTR path, std::wstring objectName, SIZE frameSize)
	:frameSize(frameSize), objectName(objectName)
{
	loadImage(path);//hSpriteImage�Ƀr�b�g�}�b�v�n���h�����i�[
	setLength(static_cast<int>(getSpriteSize().cx / frameSize.cx));//�X�v���C�g�̃R�}����ݒ�
}
void GameObject::loadImage(LPCWSTR path)
{
	setObjectImage(static_cast<HBITMAP>(LoadImage(
		NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
	)));
	if (hSpriteImage == NULL) {
		std::wstring message = L"�Q�[���I�u�W�F�N�g: " + objectName + L" �͉摜�����[�h�ł��܂���ł���\n";
		OutputDebugString(message.c_str());
	}
}

void GameObject::setPosition(POINT point)
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
	SIZE spriteSize = { -1,-1 };//hSpriteImage�̏c���T�C�Y�i�s�N�Z���j

	if (GetObject(hSpriteImage, sizeof(BITMAP), &bmp)) {
		//getObject����
		spriteSize.cx = bmp.bmWidth;
		spriteSize.cy = bmp.bmHeight;
	}
	else {
		//���s
	std::wstring message = L"�I�u�W�F�N�g: " + objectName + L" �̃r�b�g�}�b�v��GetObject�ł��܂���ł���\n";
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
		return false;//�͈͊O
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

int GameObject::getLength() const
{
	return length;
}

const HBITMAP GameObject::getSpriteImage() const
{
	return hSpriteImage;
}

const int GameObject::originOfCurrentFrame() const
{
	return getWidth() * getCurrentFrameNumber();
}
