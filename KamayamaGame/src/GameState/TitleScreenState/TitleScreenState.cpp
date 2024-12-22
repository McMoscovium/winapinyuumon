#include "GameState/TitleScreenState/TitleScreenState.h"



#include "Game/Game.h"
#include "Game/InputManager.h"
#include "Game/Window.h"
#include <Windows.h>
#include "GameState/StageListState/StageListState.h"
#include "GameObject/GameObject.h"
#include "GameState/StatusState/StatusState.h"
#include "GameObject/TextObject.h"
#include "GameObject/Pitcher/TintinPitcher.h"
#include "GameObject/Batter/KamayamaBatter.h"
#include "GameObject/Stadium/TheHundredAcreWoodStadium.h"
#include "Stage/TintinStage.h"
#include "GameObject/PictureObject.h"
#include "resource.h"
#include "include/Game/SaveData/SaveData.h"

#include <string>


TitleScreenState::TitleScreenState(Game& game, AudioManager& audioManager) :
    GameState(game, audioManager),
    saveData(SaveData(game.getCurrentVersion()))
{
    HINSTANCE hInstance = game.getHInstance();
    gameObjectManager.addFront<PictureObject>("TITLE", IDB_BITMAP19,hInstance, SIZE{ 1152,720 });
    gameObjectManager.addFront<PictureObject>("START", IDB_BITMAP21,hInstance, SIZE{ 256,128 });
    gameObjectManager.addFront<PictureObject>("STATUS", IDB_BITMAP16,hInstance, SIZE{ 256,128 });
    gameObjectManager.addFront<PictureObject>("GACHA", IDB_BITMAP8,hInstance, SIZE{ 256,128 });
    gameObjectManager.addFront<PictureObject>("QUIT", IDB_BITMAP6, hInstance, SIZE{ 256,128 });
    gameObjectManager.addFront<PictureObject>("KAMAYAMA", IDB_BITMAP10, hInstance, SIZE{ 172,178 });
    TextObject& scoreText = gameObjectManager.addFront<TextObject>("SCORE", L"");

    showAll();

    //各GameObjectの描画位置を設定@TODO
    gameObjectManager.getObject<PictureObject>("TITLE").setObjectPosition({ 0,0 });
    gameObjectManager.getObject<PictureObject>("KAMAYAMA").setObjectPosition({ 32,48 });
    gameObjectManager.getObject<PictureObject>("START").setObjectPosition({440,352});
    gameObjectManager.getObject<PictureObject>("STATUS").setObjectPosition({ 776,352 });
    gameObjectManager.getObject<PictureObject>("GACHA").setObjectPosition({ 440,528 });
    gameObjectManager.getObject<PictureObject>("QUIT").setObjectPosition({ 776,528 });
    scoreText.setObjectPosition({ 75,350 });

    //セーブデータ読み込み
    SaveDataManager saveDataManager;
    saveDataManager.load(saveData, game.getCurrentVersion());
    //スコア表示更新
    int score = saveData.getScore();
    std::wstring scorestr = L"スコア: " + std::to_wstring(score);
    scoreText.setText(scorestr);

    //BGMよみこみ
    audioManager.addWav("100ACRE", hInstance, IDR_WAVE4);   
}

TitleScreenState::~TitleScreenState()
{
}


void TitleScreenState::update(Game& game) {
    InputManager& inputManager = game.getInputManager();

    //終わるボタンクリック時
	PictureObject& quitButton = gameObjectManager.getObject<PictureObject>("QUIT");
	if (inputManager.isClicked(quitButton)) {
		OutputDebugString(L"終了ボタンがクリックされた\n");
		DestroyWindow(game.getWindow()->getHandle());
		return;
	}

    //スタートボタンクリック時
    const PictureObject& startButton = gameObjectManager.getObject<PictureObject>("START");
    if (inputManager.isClicked(startButton)) {
        OutputDebugString(L"スタートボタンがクリックされた\n");
        Stage* tintinStage = new TintinStage();
        game.changeState(new StageListState(game, audioManager, saveData.getOpenedStages()));
        return;
    }
    //ステータスボタンクリック時
    const PictureObject& statusButton = gameObjectManager.getObject<PictureObject>("STATUS");
    if (inputManager.isClicked(statusButton)) {
        OutputDebugString(L"ステータスボタンがクリックされた\n");
        game.changeState(new StatusState(game, audioManager));
        return;
    }
}

void TitleScreenState::enter(Game& game)
{
    //BGM再生
    audioManager.continueLoop("100ACRE", (UINT32)132300, (UINT32)(2381400 - 132300));
}

void TitleScreenState::exit(Game& game)
{
}
