#pragma once

#include <Windows.h>

/*
�Q�[���ɓo�ꂷ��G�A�{�^���Ȃǂ̃I�u�W�F�N�g�BBITMAP�`���ŗp�ӂ���B�A�j���[�V�������Ɏg�������͓����傫���̃r�b�g�}�b�v�����ɕ��ׂ�悤�ɂ��āA�X�v���C�g�V�[�g�̌`�ŗp�ӂ��邱�Ƃ�z�肷��B
*/
class GameObject
{
private:
	int length = 0;//�t���[���̌�
	POINT position = { 0,0 };//�I�u�W�F�N�g�̕`��ʒu
	const SIZE size;//�I�u�W�F�N�g1�t���[���́A�����`�Ƃ��Ă̏c���T�C�Y�i�s�N�Z���j
	SIZE wholeSize = { 0,0 };//�X�v���C�g�V�[�g�̃T�C�Y
	HBITMAP hObjectImage = nullptr;//�I�u�W�F�N�g�̃r�b�g�}�b�v�C���[�W

public:
	GameObject(LPCWSTR path, SIZE size);
	~GameObject() = default;
	void loadImage(LPCWSTR path);//path�̉摜���r�b�g�}�b�v�C���[�W�Ƃ���hObjectImage�Ɋi�[����B
private:
	void setLength(int);
	void setObjectImage(HBITMAP img);
};