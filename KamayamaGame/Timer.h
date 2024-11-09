#pragma once

#include <Windows.h>
#include <memory>

class Timer
{
public:
	Timer();

	//��������Ă���̎��Ԃ��X�V
	void update();
	//��������Ă���̎��Ԃ�Ԃ�
	ULONGLONG getTime()const;
	//��������Ă���̎��Ԃ����R�[�h�ɋL�^
	void recordTime();
	//���R�[�h��Ԃ�
	ULONGLONG getRecord()const;
	//���ݎ����ƃ��R�[�h�̍���Ԃ�
	ULONGLONG span()const;
	//
	bool operator>(ULONGLONG)const;
private:
	ULONGLONG time;
	ULONGLONG record;
};