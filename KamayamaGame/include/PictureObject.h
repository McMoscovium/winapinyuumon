#pragma once
#include "GameObject.h"
#include <Windows.h>

class PictureObject :
    public GameObject
{
private:
    int length;//�t���[���̌�
    const SIZE frameSize;//�I�u�W�F�N�g1�t���[���̏c���T�C�Y
    HBITMAP hSpriteImage;//�X�v���C�g�V�[�g�̃r�b�g�}�b�v�C���[�W
    int frameNumber;//���݂̃t���[���ԍ�
    COLORREF transParent = 0xff00ff;//���ߐF

    void setLength(int);
    void setObjectImage(HBITMAP img);
    bool loadImage(LPCWSTR path);//path�̉摜���r�b�g�}�b�v�C���[�W�Ƃ���hSpriteImage�Ɋi�[����B
public:
    PictureObject(std::string objectName, LPCTSTR path, SIZE frameSize);
    ~PictureObject();

    
    //length���擾
    int getLength()const;
    //hBitmap���擾
    const HBITMAP getSpriteImage()const;
    //���݂̃t���[���̌��_�̃X�v���C�g�V�[�g�ɂ�����X���W���擾����
    const int originOfCurrentFrame()const;
    //�X�v���C�g�̉摜�T�C�Y�ipx�j���擾
    SIZE getSpriteSize()const;
    //���݂̃t���[�������Ԗڂ����擾
    const int getCurrentFrameNumber()const;
    //�t���[�������ɐi�߂�i�i�߂ꂽ��true�j
    bool nextFrame();
    //�w�肵���t���[���ɕς���
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