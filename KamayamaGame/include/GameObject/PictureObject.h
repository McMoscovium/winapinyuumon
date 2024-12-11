#pragma once
#include "GameObject/GameObject.h"
#include <Windows.h>

class PictureObject :
    public GameObject
{
protected:
    int length;//フレームの個数
    const SIZE frameSize;//オブジェクト1フレームの縦横サイズ
    HBITMAP hSpriteImage;//スプライトシートのビットマップイメージ
    int frameNumber;//現在のフレーム番号
    COLORREF transParent = 0xff00ff;//透過色
    int rotate = 0;//回転角

    void setLength(int);
    void setObjectImage(HBITMAP img);
    bool loadImage(LPCWSTR path);//pathの画像をビットマップイメージとしてhSpriteImageに格納する。
public:
    PictureObject(const std::string& objectName, const LPCTSTR& path, const SIZE& frameSize);
    PictureObject(const std::string& objectName, const int resourceId,const HINSTANCE& hInstance, const SIZE& frameSize);
    virtual ~PictureObject();

    
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
    virtual bool nextFrame();
    //指定したフレームに変える
    bool changeFrame(int);
    //
    void deleteHBITMAP();
    //
    void render(HDC hdc)const override;
    //
    const RECT getObjectRect()const;
    //
    const int getWidth()const;
    //
    const int getHeight()const;
    //
    const int getWidthOnWindow()const;
    //
    const int getHeightOnWindow()const;
    //
    bool isIntersectsWithClientRect(Window* window);
};