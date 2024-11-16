#include "PlayResultState.h"

#include "CompareNormSubState.h"
#include "TextObject.h"
#include "Pitcher.h"

#include <string>


PlayResultState::PlayResultState(Game& game, Result& result,Pitcher* pitcher):
	GameState(game),
	result(result)
{
	OutputDebugString(L"Entering PlayResultState\n");

	//GameObjectよみこみ
	appendObject(L"PICTURE_KEKKAHAPPYOU", L".//assets//結果発表.bmp", { 1152,720 });//背景
	//appendObject({バッター画像オブジェクトへのポインター});//バッター画像

	std::wstring pitcherName = pitcher->getName();
	appendObject(new TextObject(L"TEXT_PITCHERNAME", pitcherName));//ピッチャー名
	

	appendObject(new TextObject(L"TEXT_BALLS", L"1oku"));//球数
	appendObject(new TextObject(L"TEXT_NORM", L"1oku"));//ノルマ
	std::wstring runs = std::to_wstring(result.getRuns());
	appendObject(new TextObject(L"TEXT_RUNS", runs));//ホームラン数
	appendObject(L"PICTURE_CLEAR", L".//assets//クリア.bmp", { 273,78 });
	appendObject(L"PICTURE_FAILURE", L".//assets//しっぱい.bmp", { 273,78 });
	appendObject(L"BUTTON_NEXT", L".//assets//次へ.bmp", { 115,49 });

	//位置設定
	getGameObject(L"TEXT_PITCHERNAME").setObjectPosition({ 312,224 });
	getGameObject(L"TEXT_BALLS").setObjectPosition({ 606,330 });
	getGameObject(L"TEXT_NORM").setObjectPosition({ 606,393 });
	getGameObject(L"TEXT_RUNS").setObjectPosition({ 741,514 });
	getGameObject(L"BUTTON_NEXT").setObjectPosition({ 920,623 });

	//substate初期化
	changeSubState(new CompareNormSubState(*this));
}

PlayResultState::~PlayResultState()
{
	//ポインタ型のメンバがいたらdelete
}

void PlayResultState::update(Game& game)
{
	if (currentSubState)currentSubState->update(game);
}

const Result& PlayResultState::getResult() const
{
	return result;
}
