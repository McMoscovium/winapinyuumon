#pragma once

#include <Windows.h>

/*
ゲームに登場する絵、ボタンなどのオブジェクト。BITMAP形式で用意する。アニメーション等に使う差分は同じ大きさのビットマップを横に並べるようにして、スプライトシートの形で用意することを想定する。
*/
class GameObject
{
private:
	int length = 0;//フレームの個数
	POINT position = { 0,0 };//オブジェクトの描画位置
	const SIZE size;//オブジェクト1フレームの、長方形としての縦横サイズ（ピクセル）
	SIZE wholeSize = { 0,0 };//スプライトシートのサイズ
	HBITMAP hObjectImage = nullptr;//オブジェクトのビットマップイメージ

public:
	GameObject(LPCWSTR path, SIZE size);
	~GameObject() = default;
	void loadImage(LPCWSTR path);//pathの画像をビットマップイメージとしてhObjectImageに格納する。
private:
	void setLength(int);
	void setObjectImage(HBITMAP img);
};