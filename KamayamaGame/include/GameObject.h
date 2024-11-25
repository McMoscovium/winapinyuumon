#pragma once

#include <Windows.h>
#include <string>


class Window;


/*
ゲームに登場する絵、ボタンなどのオブジェクト。BITMAP形式で用意する。アニメーション等に使う差分は同じ大きさのビットマップを横に並べるようにして、スプライトシートの形で用意することを想定する。
*/
class GameObject
{
protected:
	bool visible = false;//trueで描画される
	std::string objectName;
	POINT position = { 0,0 };//オブジェクトの描画位置
	float sizeRate = 1.0f;//何倍に拡大して描画するか

public:
	GameObject(const std::string& objectName);
	virtual ~GameObject();

	//positionの変更
	void setObjectPosition(POINT);
	//描画される位置を取得
	const POINT getPosition()const;
	//描画される場所のX座標の取得
	const int getPositionX()const;
	//描画される場所のY座標の取得
	const int getPositionY()const;	
	//
	float getSizeRate()const;
	
	//visibleかどうか返す
	bool isVisible()const;
	//visibleにする
	void appear();
	//invisibleにする
	void hide();
	
	//
	void changeSizeRate(float r);
	//与えられたHDCに自身を描画する
	virtual void render(HDC hdc)const = 0;
	//オブジェクト名へのconst参照を返す
	const std::string& getName()const;	
};