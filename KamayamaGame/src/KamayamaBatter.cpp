#include"GameOBject/Batter/KamayamaBatter.h"
#include "resource.h"

using namespace std;

KamayamaBatter::KamayamaBatter(HINSTANCE hInstance) :
	Batter(
		(L"kamayama"),
		25,//パワー
		4.0f,//スピード
		50,//ミート
		IDB_BITMAP41,
		hInstance,
		SIZE{ 360,391 }
	)
{
}
