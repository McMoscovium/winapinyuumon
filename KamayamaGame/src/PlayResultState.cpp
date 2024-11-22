#include "PlayResultState.h"

#include "CompareNormSubState.h"
#include "TextObject.h"
#include "Stage.h"
#include "Pitcher.h"
#include <string>


PlayResultState::PlayResultState(Game& game, Result& result, Stage* stage) :
	GameState(game),
	result(result)
{
	OutputDebugString(L"Entering PlayResultState\n");

	//GameObjectよみこみ
	gameObjectManager.addFront<PictureObject>("KEKKAHAPPYOU", L".//assets//結果発表.bmp", SIZE{ 1152,720 });
	gameObjectManager.addFront<PictureObject>("KEKKAHAPPYOU2", L".//assets//結果発表2.bmp", SIZE{ 1152,720 });
	
	//appendObject({バッター画像オブジェクトへのポインター});//バッター画像

	Pitcher* pitcher = stage->getPitcher();
	gameObjectManager.addFront<TextObject>("PITCHERNAME", pitcher->getName());
	gameObjectManager.addFront<TextObject>("BALLS", std::to_wstring(stage->getTrials()));
	gameObjectManager.addFront<TextObject>("NORM", std::to_wstring(stage->getNorm()));
	gameObjectManager.addFront<TextObject>("RUNS", std::to_wstring(result.getRuns()));
	gameObjectManager.addFront<TextObject>("RUNSTREAK", std::to_wstring(result.getMaxSuccessiveRuns()));
	gameObjectManager.addFront<TextObject>("MAX_DISTANCE", std::to_wstring(result.getMaxDistance()));
	gameObjectManager.addFront<TextObject>("DISTANCE_SUM", std::to_wstring(result.getDistanceSum()));
	gameObjectManager.addFront<TextObject>("BONUS_POINT", L"0");
	gameObjectManager.addFront<PictureObject>("CLEAR", L".//assets//クリア.bmp", SIZE{ 273,78 });
	gameObjectManager.addFront<PictureObject>("FAILURE", L".//assets//しっぱい.bmp", SIZE{ 273,78 });
	gameObjectManager.addFront<PictureObject>("NEXT", L".//assets//次へ.bmp", SIZE{ 115,49 });
	PictureObject& toStageList = gameObjectManager.addFront<PictureObject>("TO_STAGELIST", L".//assets//ステージ選択へ.bmp", SIZE{ 401,66 });

	//位置設定
	gameObjectManager.getObject<PictureObject>("PITCHERNAME").setObjectPosition({ 312,224 });
	gameObjectManager.getObject<TextObject>("BALLS").setObjectPosition({ 606,330 });
	gameObjectManager.getObject<TextObject>("NORM").setObjectPosition({ 606,393 });
	gameObjectManager.getObject<TextObject>("RUNS").setObjectPosition({ 741,514 });
	gameObjectManager.getObject<PictureObject>("NEXT").setObjectPosition({ 920,623 });
	toStageList.setObjectPosition({ 718,643 });

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
