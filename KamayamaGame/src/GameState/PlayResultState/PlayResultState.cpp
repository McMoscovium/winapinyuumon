#include "GameState/PlayResultState/PlayResultState.h"

#include "GameState/PlayResultState/CompareNormSubState.h"
#include "GameObject/TextObject.h"
#include "Stage/Stage.h"
#include "Game/Game.h"
#include "GameObject/Pitcher/Pitcher.h"
#include <string>
#include "include/Game/SaveData/SaveData.h"
#include "resource.h"
#include <sstream>
#include <iomanip>


PlayResultState::PlayResultState(Game& game, AudioManager& audioManager, Result& result, const int trials, const int norm, const std::wstring& pitcherName, const char stageNumber, const float scoreFactor) :
	GameState(game, audioManager),
	result(result),
	saveData(SaveData(game.getCurrentVersion())),
	openedStages(1)
{
	HINSTANCE hInstance = game.getHInstance();
	//GameObjectよみこみ
	gameObjectManager.addFront<PictureObject>("KEKKAHAPPYOU", IDB_BITMAP36, hInstance, SIZE{ 1152,720 });
	gameObjectManager.addFront<PictureObject>("KEKKAHAPPYOU2", IDB_BITMAP37, hInstance, SIZE{ 1152,720 });
	
	//appendObject({バッター画像オブジェクトへのポインター});//バッター画像
	gameObjectManager.addFront<TextObject>("PITCHERNAME", pitcherName);
	gameObjectManager.addFront<TextObject>("BALLS", std::to_wstring(trials));
	gameObjectManager.addFront<TextObject>("NORM", std::to_wstring(norm));
	gameObjectManager.addFront<TextObject>("RUNS", std::to_wstring(result.getRuns()));
	gameObjectManager.addFront<TextObject>("RUNSTREAK", std::to_wstring(result.getMaxSuccessiveRuns()));
	gameObjectManager.addFront<TextObject>("MAX_DISTANCE", std::to_wstring(result.getMaxDistance()));
	gameObjectManager.addFront<TextObject>("DISTANCE_SUM", std::to_wstring(result.getDistanceSum()));
	TextObject& point = gameObjectManager.addFront<TextObject>("BONUS_POINT", L"0");
	gameObjectManager.addFront<PictureObject>("CLEAR", IDB_BITMAP11, hInstance, SIZE{ 273,78 });
	gameObjectManager.addFront<PictureObject>("FAILURE", IDB_BITMAP13, hInstance, SIZE{ 273,78 });
	gameObjectManager.addFront<PictureObject>("NEXT", IDB_BITMAP39, hInstance, SIZE{ 115,49 });
	PictureObject& toStageList = gameObjectManager.addFront<PictureObject>("TO_STAGELIST", IDB_BITMAP15, hInstance, SIZE{ 401,66 });

	//位置設定
	gameObjectManager.getObject<PictureObject>("PITCHERNAME").setObjectPosition({ 312,224 });
	gameObjectManager.getObject<TextObject>("BALLS").setObjectPosition({ 606,330 });
	gameObjectManager.getObject<TextObject>("NORM").setObjectPosition({ 606,393 });
	gameObjectManager.getObject<TextObject>("RUNS").setObjectPosition({ 741,514 });
	gameObjectManager.getObject<PictureObject>("NEXT").setObjectPosition({ 920,623 });
	toStageList.setObjectPosition({ 718,643 });

	//スコアデータ更新処理
	//データ読み込み
	SaveDataManager saveDataManager;
	SaveData prevData(game.getCurrentVersion());
	saveDataManager.load(prevData, game.getCurrentVersion());
	//新ステージ開放処理
	if (
		stageNumber >= prevData.getOpenedStages()&&//最新ステージをプレイ
		result.getRuns() >= norm//ノルマクリア
		) {
		prevData.addOpenedStages();
	}
	//スコア加算
	int score = result.getDistanceSum();
	saveData = prevData.addScore((int)(score * scoreFactor));
	openedStages = saveData.getOpenedStages();
	//セーブ
	saveDataManager.save(saveData);

	//スコア文字変更
	std::wstringstream wss;
	wss << std::fixed << std::setprecision(1) << scoreFactor;
	std::wstring scoreFactorStr = wss.str();
	std::wstring scorestr = std::to_wstring(prevData.getScore()) + L" + " + std::to_wstring(score) + L" × " + scoreFactorStr + L" = " + std::to_wstring(saveData.getScore());
	point.setText(scorestr);

	//全ての音楽を停止
	audioManager.stopAll();
	//プレイBGM削除
	audioManager.deleteWav("BGM1");
	audioManager.deleteWav("JUST");

	//結果発表bgm追加
	audioManager.addWav("RESULT", hInstance, IDR_WAVE5);

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

void PlayResultState::enter(Game& game)
{
	audioManager.stopAll();
	audioManager.play("RESULT", true);
}

void PlayResultState::exit(Game& game)
{
	audioManager.stopAll();
	audioManager.deleteWav("RESULT");
}

const Result& PlayResultState::getResult() const
{
	return result;
}
