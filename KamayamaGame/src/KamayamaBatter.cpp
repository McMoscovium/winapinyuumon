#include"GameOBject/Batter/KamayamaBatter.h"
#include "resource.h"

using namespace std;

KamayamaBatter::KamayamaBatter(HINSTANCE hInstance) :
	Batter(
		(L"kamayama"),
		25,//�p���[
		4.0f,//�X�s�[�h
		50,//�~�[�g
		IDB_BITMAP41,
		hInstance,
		SIZE{ 360,391 }
	)
{
}
