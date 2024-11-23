#include"KamayamaBatter.h"

using namespace std;

KamayamaBatter::KamayamaBatter() :
	Batter(
		(L"kamayama"),
		25,//パワー
		4.0f,//スピード
		50,//ミート
		(L".//assets//打者.bmp"),
		SIZE{ 360,391 }
	)
{
}
