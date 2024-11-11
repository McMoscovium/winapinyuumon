#pragma once

#include <Windows.h>
#include <string>


class Window;


/*
�Q�[���ɓo�ꂷ��G�A�{�^���Ȃǂ̃I�u�W�F�N�g�BBITMAP�`���ŗp�ӂ���B�A�j���[�V�������Ɏg�������͓����傫���̃r�b�g�}�b�v�����ɕ��ׂ�悤�ɂ��āA�X�v���C�g�V�[�g�̌`�ŗp�ӂ��邱�Ƃ�z�肷��B
*/
class GameObject
{
private:
	bool visible = true;//true�ŕ`�悳���
	std::wstring objectName;
	int length;//�t���[���̌�
	POINT position = { 0,0 };//�I�u�W�F�N�g�̕`��ʒu
	const SIZE frameSize;//�I�u�W�F�N�g1�t���[���́A�����`�Ƃ��Ă̏c���T�C�Y�i�s�N�Z���j
	HBITMAP hSpriteImage = nullptr;//�X�v���C�g�V�[�g�̃r�b�g�}�b�v�C���[�W
	int frameNumber = 0;//���A�X�v���C�g�̉��t���[���ڂ��i0����n�܂�j
	COLORREF transparent = 0xff00ff;//���ߐF

public:
	GameObject(LPCTSTR path, std::wstring objectName, SIZE frameSize);
	~GameObject() = default;

	//position�̕ύX
	void setObjectPosition(POINT);
	//�`�悳���ʒu���擾
	const POINT getPosition()const;
	//�`�悳���ꏊ��X���W�̎擾
	const int getPositionX()const;
	//�`�悳���ꏊ��Y���W�̎擾
	const int getPositionY()const;
	//1�t���[���̐��@�i�c���j���擾
	const RECT getObjectRect()const;
	//1�t���[���̕����擾
	const int getWidth()const;
	//1�t���[���̍������擾
	const int getHeight()const;
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
	//visible���ǂ����Ԃ�
	bool isVisible()const;
	//visible�ɂ���
	void appear();
	//invisible�ɂ���
	void hide();
	//window�̃N���C�A���g�̈���ɂ��邩���ׂ�
	bool isOutOfClientRect(Window* window);
	
private:
	void setLength(int);
	void setObjectImage(HBITMAP img);
	void loadImage(LPCWSTR path);//path�̉摜���r�b�g�}�b�v�C���[�W�Ƃ���hSpriteImage�Ɋi�[����B
};