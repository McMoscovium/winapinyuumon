#include "PlayResultState.h"

#include "CompareNormSubState.h"
#include "TextObject.h"
#include "Pitcher.h"

#include <string>


PlayResultState::PlayResultState(Game& game, Result& result, Pitcher* pitcher) :
	GameState(game),
	result(result)
{
	OutputDebugString(L"Entering PlayResultState\n");

	//GameObjectよみこみ
	gameObjectManager.addFront<PictureObject>("KEKKAHAPPYOU", L".//assets//結果発表.bmp", SIZE{ 1152,720 });
	
	//appendObject({バッター画像オブジェクトへのポインター});//バッター画像
	gameObjectManager.addFront<TextObject>("PITCHERNAME", pitcher->getName());
	gameObjectManager.addFront<TextObject>("BALLS", L"1oku");
	gameObjectManager.addFront<TextObject>("NORM", L"1oku");
	gameObjectManager.addFront<TextObject>("RUNS", std::to_wstring(result.getRuns()));
	gameObjectManager.addFront<PictureObject>("CLEAR", L".//assets//クリア.bmp", SIZE{ 273,78 });
	gameObjectManager.addFront<PictureObject>("FAILURE", L".//assets//しっぱい.bmp", SIZE{ 273,78 });
	gameObjectManager.addFront<PictureObject>("NEXT", L".//assets//次へ.bmp", SIZE{ 115,49 });

	//位置設定
	gameObjectManager.getObject<PictureObject>("PITCHERNAME").setObjectPosition({ 312,224 });
	gameObjectManager.getObject<TextObject>("BALLS").setObjectPosition({ 606,330 });
	gameObjectManager.getObject<TextObject>("NORM").setObjectPosition({ 606,393 });
	gameObjectManager.getObject<TextObject>("RUNS").setObjectPosition({ 741,514 });
	gameObjectManager.getObject<PictureObject>("NEXT").setObjectPosition({ 920,623 });

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
