#pragma once

#include <Windows.h>

class Window;

/// <summary>
/// ���z�E�B���h�E�B����ɃQ�[����Ԃ�`�悵��Window�N���X�Ƀf�[�^�𑗂�A���ۂ̃E�B���h�E�ɕ`�悵�Ă��炤�B
/// </summary>
class VirtualWindow
{
public:
	VirtualWindow(Window* window);//window�ƌ݊����������z�E�B���h�E�i�o�b�N�o�b�t�@�j�N���X���쐬
	~VirtualWindow();
private:
	HDC hdcBackBuffer = nullptr;//�o�b�N�o�b�t�@�p�������f�o�C�X�R���e�X�g
	HBITMAP hBackBuffer = nullptr;//�o�b�N�o�b�t�@�p�r�b�g�}�b�v�i�������f�o�C�X�R���e�L�X�g�̓r�b�g�}�b�v��ɕ`�悷��B�j
};