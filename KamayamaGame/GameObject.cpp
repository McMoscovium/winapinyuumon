#include "GameObject.h"
//開発用
#include <iostream>

GameObject::GameObject(LPCWSTR path, SIZE size)
	:size(size)
{
	loadImage(path);
	BITMAP bmp;
	if (GetObject(hObjectImage, sizeof(BITMAP), &bmp)) {
		wholeSize.cx = bmp.bmWidth;
		wholeSize.cy = bmp.bmHeight;
	}
	else {
		std::cout << "読み込み失敗" << std::endl;
		wholeSize = { 0,0 };
	}
	
	length = static_cast<int>(wholeSize.cx / size.cy);
	//以下テスト用
	std::cout << "length: " << length;
}
void GameObject::loadImage(LPCWSTR path)
{
	setObjectImage(static_cast<HBITMAP>(LoadImage(
		NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
	)));
	if (hObjectImage == NULL) {
		//読み込み失敗
	}
}

void GameObject::setLength(int l) {
	length = l;
}

void GameObject::setObjectImage(HBITMAP img) {
	hObjectImage = img;
}