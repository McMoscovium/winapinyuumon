#pragma once

#include <Windows.h>
#include <string>


class Window;


/*
�Q�[���ɓo�ꂷ��G�A�{�^���Ȃǂ̃I�u�W�F�N�g�BBITMAP�`���ŗp�ӂ���B�A�j���[�V�������Ɏg�������͓����傫���̃r�b�g�}�b�v�����ɕ��ׂ�悤�ɂ��āA�X�v���C�g�V�[�g�̌`�ŗp�ӂ��邱�Ƃ�z�肷��B
*/
class GameObject
{
protected:
	bool visible = false;//true�ŕ`�悳���
	std::string objectName;
	POINT position = { 0,0 };//�I�u�W�F�N�g�̕`��ʒu
	float sizeRate = 1.0f;//���{�Ɋg�債�ĕ`�悷�邩

public:
	GameObject(const std::string& objectName);
	virtual ~GameObject();

	//position�̕ύX
	void setObjectPosition(POINT);
	//�`�悳���ʒu���擾
	const POINT getPosition()const;
	//�`�悳���ꏊ��X���W�̎擾
	const int getPositionX()const;
	//�`�悳���ꏊ��Y���W�̎擾
	const int getPositionY()const;	
	//
	float getSizeRate()const;
	
	//visible���ǂ����Ԃ�
	bool isVisible()const;
	//visible�ɂ���
	void appear();
	//invisible�ɂ���
	void hide();
	
	//
	void changeSizeRate(float r);
	//�^����ꂽHDC�Ɏ��g��`�悷��
	virtual void render(HDC hdc)const = 0;
	//�I�u�W�F�N�g���ւ�const�Q�Ƃ�Ԃ�
	const std::string& getName()const;	
};