#pragma once

#include <Windows.h>
#include <string>


class Window;


/*
ゲームに登場する絵、ボタンなどのオブジェクト。BITMAP形式で用意する。アニメーション等に使う差分は同じ大きさのビットマップを横に並べるようにして、スプライトシートの形で用意することを想定する。
*/
class GameObject
{
private:
	bool visible = true;//trueで描画される
	std::wstring objectName;
	int length;//フレームの個数
	POINT position = { 0,0 };//オブジェクトの描画位置
	const SIZE frameSize;//オブジェクト1フレームの、長方形としての縦横サイズ（ピクセル）
	HBITMAP hSpriteImage = nullptr;//スプライトシートのビットマップイメージ
	int frameNumber = 0;//今、スプライトの何フレーム目か（0から始まる）
	COLORREF transparent = 0xff00ff;//透過色

public:
	GameObject(LPCTSTR path, std::wstring objectName, SIZE frameSize);
	~GameObject() = default;

	//positionの変更
	void setObjectPosition(POINT);
	//描画される位置を取得
	const POINT getPosition()const;
	//描画される場所のX座標の取得
	const int getPositionX()const;
	//描画される場所のY座標の取得
	const int getPositionY()const;
	//1フレームの寸法（縦横）を取得
	const RECT getObjectRect()const;
	//1フレームの幅を取得
	const int getWidth()const;
	//1フレームの高さを取得
	const int getHeight()const;
	//lengthを取得
	int getLength()const;
	//hBitmapを取得
	const HBITMAP getSpriteImage()const;
	//現在のフレームの原点のスプライトシートにおけるX座標を取得する
	const int originOfCurrentFrame()const;
	//スプライトの画像サイズ（px）を取得
	SIZE getSpriteSize()const;
	//現在のフレームが何番目かを取得
	const int getCurrentFrameNumber()const;
	//フレームを次に進める（進めれたらtrue）
	bool nextFrame();
	//指定したフレームに変える
	bool changeFrame(int);
	//visibleかどうか返す
	bool isVisible()const;
	//visibleにする
	void appear();
	//invisibleにする
	void hide();
	//windowのクライアント領域内にあるか調べる
	bool isOutOfClientRect(Window* window);
	
private:
	void setLength(int);
	void setObjectImage(HBITMAP img);
	void loadImage(LPCWSTR path);//pathの画像をビットマップイメージとしてhSpriteImageに格納する。
};