#include "GameState/TitleScreenState/TitleScreenState.h"



#include "Game/Game.h"
#include "Game/InputManager.h"
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


TitleScreenState::TitleScreenState(Game& game) :
    GameState(game)
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

    //�eGameObject�̕`��ʒu��ݒ�@TODO
    gameObjectManager.getObject<PictureObject>("TITLE").setObjectPosition({ 0,0 });
    gameObjectManager.getObject<PictureObject>("KAMAYAMA").setObjectPosition({ 32,48 });
    gameObjectManager.getObject<PictureObject>("START").setObjectPosition({440,352});
    gameObjectManager.getObject<PictureObject>("STATUS").setObjectPosition({ 776,352 });
    gameObjectManager.getObject<PictureObject>("GACHA").setObjectPosition({ 440,528 });
    gameObjectManager.getObject<PictureObject>("QUIT").setObjectPosition({ 776,528 });
    scoreText.setObjectPosition({ 75,350 });

    //�Z�[�u�f�[�^�ǂݍ���
    SaveData saveData(game.getCurrentVersion());
    SaveDataManager saveDataManager;
    saveDataManager.load(saveData, game.getCurrentVersion());
    //�X�R�A�\���X�V
    int score = saveData.getScore();
    std::wstring scorestr = L"�X�R�A: " + std::to_wstring(score);
    scoreText.setText(scorestr);
}


void TitleScreenState::update(Game& game) {
    //�^�C�g����ʂ̍X�V����@TODO

    //�I���{�^���N���b�N��@TODO

    InputManager& inputManager = game.getInputManager();

    //�X�^�[�g�{�^���N���b�N��
    const PictureObject& startButton = gameObjectManager.getObject<PictureObject>("START");
    if (inputManager.isClicked(startButton)) {
        OutputDebugString(L"�X�^�[�g�{�^�����N���b�N���ꂽ\n");
        Stage* tintinStage = new TintinStage();
        game.changeState(new StageListState(game));
        return;
    }
    //�X�e�[�^�X�{�^���N���b�N��
    const PictureObject& statusButton = gameObjectManager.getObject<PictureObject>("STATUS");
    if (inputManager.isClicked(statusButton)) {
        OutputDebugString(L"�X�e�[�^�X�{�^�����N���b�N���ꂽ\n");
        game.changeState(new StatusState(game));
        return;
    }
}