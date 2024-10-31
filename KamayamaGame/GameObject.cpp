#include "GameObject.h"
//�J���p
#include <iostream>
#include <string>

GameObject::GameObject(LPCTSTR path, std::string objectName, SIZE frameSize)
	:frameSize(frameSize), objectName(objectName)
{
	loadImage(path);//hSpriteImage�Ƀr�b�g�}�b�v�n���h�����i�[
	setLength(static_cast<int>(getSpriteSize().cx / frameSize.cx));//�X�v���C�g�̃R�}����ݒ�
	//�ȉ��e�X�g�p
	std::cout << objectName << " ��length: " << length << std::endl;
}
void GameObject::loadImage(LPCWSTR path)
{
	setObjectImage(static_cast<HBITMAP>(LoadImage(
		NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
	)));
	if (hSpriteImage == NULL) {
		//�ǂݍ��ݎ��s
		std::cout << "�Q�[���I�u�W�F�N�g " << objectName << " �͉摜�����[�h�ł��܂���ł���" << std::endl;
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
	SIZE spriteSize = { -1,-1 };//hSpriteImage�̏c���T�C�Y�i�s�N�Z���j

	if (GetObject(hSpriteImage, sizeof(BITMAP), &bmp)) {
		//getObject����
		spriteSize.cx = bmp.bmWidth;
		spriteSize.cy = bmp.bmHeight;
	}
	else {
		//���s
		std::cout << "�I�u�W�F�N�g " << objectName << "�̃r�b�g�}�b�v��GetObject�ł��܂���ł����B" << std::endl;
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
