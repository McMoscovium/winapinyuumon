#include "GameState/PlayingState/PlayingState.h"

#include "Game/Game.h"
#include "GameState/GameSubState.h"
#include "GameState/GameOverState/GameOverState.h"
#include "Game/InputManager.h"
#include "GameState/PlayingState/InPitchingSubState.h"
#include "GameState/PlayingState/WaitingPitchingSubState.h"
#include "util/Vector2D.h"
#include "GameObject/Pitcher/TintinPitcher.h"
#include "GameObject/TextObject.h"
#include "GameObject/Batter/Batter.h"
#include "GameObject/Stadium/Stadium.h"
#include "./resource.h"

#include "Stage/Stage.h"

#include <algorithm>

#include"GameState/TitleScreenState/TitleScreenState.h"

#include <typeinfo>





PlayingState::PlayingState(Game& game, Stage* stage) :
    GameState(game),
    stage(stage),
    stadium(stage->createStadium()),
    result(Result(stage->getNorm())),
    restBalls(stage->getTrials())
{
    HINSTANCE hInstance = game.getHInstance();
    //フィールド画像読み込み
    gameObjectManager.addFront<PictureObject>("FIELD00", IDB_BITMAP25, hInstance, SIZE{ 1920,1200 });
    gameObjectManager.addFront<PictureObject>("FIELD01", IDB_BITMAP26, hInstance, SIZE{ 1920,1200 });
    gameObjectManager.addFront<PictureObject>("FIELD02", IDB_BITMAP27, hInstance, SIZE{ 1920,1200 });
    gameObjectManager.addFront<PictureObject>("FIELD10", IDB_BITMAP28, hInstance, SIZE{ 1920,1200 });
    gameObjectManager.addFront<PictureObject>("FIELD11", IDB_BITMAP30, hInstance, SIZE{ 1920,1200 });
    gameObjectManager.addFront<PictureObject>("FIELD12", IDB_BITMAP32, hInstance, SIZE{ 1920,1200 });
    gameObjectManager.addFront<PictureObject>("FIELD-10", IDB_BITMAP29, hInstance, SIZE{ 1920,1200 });
    gameObjectManager.addFront<PictureObject>("FIELD-11", IDB_BITMAP31, hInstance, SIZE{ 1920,1200 });
    gameObjectManager.addFront<PictureObject>("FIELD-12", IDB_BITMAP33, hInstance, SIZE{ 1920,1200 });

    //フィールド画像だけ別のコンテナにも入れる
    fieldImages.emplace("FIELD00", gameObjectManager.getObject<PictureObject>("FIELD00"));
    fieldImages.emplace("FIELD01", gameObjectManager.getObject<PictureObject>("FIELD01"));
    fieldImages.emplace("FIELD02", gameObjectManager.getObject<PictureObject>("FIELD02"));
    fieldImages.emplace("FIELD10", gameObjectManager.getObject<PictureObject>("FIELD10"));
    fieldImages.emplace("FIELD11", gameObjectManager.getObject<PictureObject>("FIELD11"));
    fieldImages.emplace("FIELD12", gameObjectManager.getObject<PictureObject>("FIELD12"));
    fieldImages.emplace("FIELD-10", gameObjectManager.getObject<PictureObject>("FIELD-10"));
    fieldImages.emplace("FIELD-11", gameObjectManager.getObject<PictureObject>("FIELD-11"));
    fieldImages.emplace("FIELD-12", gameObjectManager.getObject<PictureObject>("FIELD-12"));
    


    //他の画像も読み込み
    gameObjectManager.addFront<PictureObject>("FIELD", IDB_BITMAP24, hInstance, SIZE{ 1152,720 });

    gameObjectManager.addFrontDirect<Pitcher>("PITCHER", stage->createPitcher(hInstance));
    gameObjectManager.addFrontDirect<Batter>("BATTER", stage->createBatter(hInstance));
    gameObjectManager.addFront<PictureObject>("EXIT", IDB_BITMAP6,hInstance, SIZE{ 256,128 });
    gameObjectManager.addFront<PictureObject>("BALL", IDB_BITMAP34, hInstance, SIZE{ 41,50 });
    gameObjectManager.addFront<PictureObject>("BALLSHADOW", IDB_BITMAP35, hInstance, SIZE{ 33,37 });
    gameObjectManager.addFront<PictureObject>("BAT_HITBOX", L".//assets//batHitBox.bmp", SIZE{ 50,50 });
    gameObjectManager.addFront<PictureObject>("FINISH", IDB_BITMAP12, hInstance, SIZE{ 680,158 });

    //ここでテキストオブジェクトいっときますか
    TextObject& normText = gameObjectManager.addFront<TextObject>("NORM", std::to_wstring(stage->getNorm()));
    TextObject& runsText = gameObjectManager.addFront<TextObject>("RUNS", std::to_wstring(0));
    TextObject& restText = gameObjectManager.addFront<TextObject>("REST", std::to_wstring(stage->getTrials()));
    gameObjectManager.addFront<TextObject>("DISTANCE", L"");
    gameObjectManager.addFront<TextObject>("RESULT", L"");

    //カットイン用画像
    gameObjectManager.addFront<PictureObject>("CUTIN", IDB_BITMAP44, game.getHInstance(), SIZE{ 2000,365 });
    gameObjectManager.addFront<PictureObject>("CUTIN_STRING", IDB_BITMAP45, game.getHInstance(), SIZE{ 1289,200 });

    //各GameObjectの描画位置を設定
    gameObjectManager.getObject<PictureObject>("FIELD").setObjectPosition({0,0});
    gameObjectManager.getObject<PictureObject>("BATTER").setObjectPosition({ 32,48 });
    gameObjectManager.getObject<PictureObject>("EXIT").setObjectPosition({ 850,500 });
    gameObjectManager.getObject<PictureObject>("PITCHER").setObjectPosition({ 514, 22 });
    normText.setObjectPosition({ 166,121 });
    runsText.setObjectPosition({ 192,198 });
    restText.setObjectPosition({ 160,259 });
    
    //各テキストを初期化
    std::wstring normString = std::to_wstring(stage->getNorm());
    gameObjectManager.getObject<TextObject>("NORM").setText(normString);
    gameObjectManager.getObject<TextObject>("NORM").setObjectPosition({ 229,125 });
    gameObjectManager.getObject<TextObject>("RUNS").setText(L"0");
    gameObjectManager.getObject<TextObject>("RUNS").setObjectPosition({ 229,188 });
    std::wstring restString = std::to_wstring(stage->getTrials());
    gameObjectManager.getObject<TextObject>("REST").setText(restString);
    gameObjectManager.getObject<TextObject>("REST").setObjectPosition({ 229,272 });

    //オーディオファイルの読み込み
    audioManager.addWav("BGM1", hInstance, IDR_WAVE3);
    audioManager.addWav("JUST", hInstance, IDR_WAVE2);

    audioManager.play("BGM1", true);

    changeSubState(new WaitingPitchingSubState(*this));
}

PlayingState::PlayingState(Game& game, Stage* stage, GameObjectManager&& gameObjectManager, AudioManager&& audioManager) :
    GameState(game),
    stage(stage),
    stadium(stage->createStadium()),
    result(Result(stage->getNorm())),
    restBalls(stage->getTrials())
{
    gameObjectManager = std::move(gameObjectManager);
    audioManager = std::move(audioManager);

    //フィールド画像だけ別のコンテナにも入れる
    fieldImages.emplace("FIELD00", gameObjectManager.getObject<PictureObject>("FIELD00"));
    fieldImages.emplace("FIELD01", gameObjectManager.getObject<PictureObject>("FIELD01"));
    fieldImages.emplace("FIELD02", gameObjectManager.getObject<PictureObject>("FIELD02"));
    fieldImages.emplace("FIELD10", gameObjectManager.getObject<PictureObject>("FIELD10"));
    fieldImages.emplace("FIELD11", gameObjectManager.getObject<PictureObject>("FIELD11"));
    fieldImages.emplace("FIELD12", gameObjectManager.getObject<PictureObject>("FIELD12"));
    fieldImages.emplace("FIELD-10", gameObjectManager.getObject<PictureObject>("FIELD-10"));
    fieldImages.emplace("FIELD-11", gameObjectManager.getObject<PictureObject>("FIELD-11"));
    fieldImages.emplace("FIELD-12", gameObjectManager.getObject<PictureObject>("FIELD-12"));

    //音楽再生
    audioManager.play("BGM1", true);

    //最後にsubState設定
    changeSubState(new WaitingPitchingSubState(*this));
}

PlayingState::~PlayingState()
{
    if (stage) {
        delete stage;
        stage = nullptr;
    }
}

void PlayingState::update(Game& game) {
    if (currentSubState)currentSubState->update(game);
}

void PlayingState::updateBatFrame(int currentBatterFrame)
{
    POINT batterPos = gameObjectManager.getObject<PictureObject>("BATTER").getPosition();
    //バット判定枠移動
    POINT framePos = { getCursorPos().x - 25,
        getCursorPos().y - 25 - (currentBatterFrame - 3) * 25 };
    PictureObject& batHitBox = gameObjectManager.getObject<PictureObject>("BAT_HITBOX");
    batHitBox.setObjectPosition(framePos);
    //バット判定枠の出現
    batHitBox.appear();
}

void PlayingState::updateBatterAnimation(const InputManager& inputManager)
{
    //釜山のスイング処理
    PictureObject & batter = gameObjectManager.getObject<PictureObject>("BATTER");
    const int kamayamaFrame = batter.getCurrentFrameNumber();
    if (kamayamaFrame == 0) {//スイングしてない
        if (inputManager.getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_PRESSED) {
            releasedLeftButtonUntilSwingEnded = false;
            batter.nextFrame();
            //OutputDebugString(L"スイング開始\n");
        }
    }
    else if (kamayamaFrame < batter.getLength() - 1) {//スイング途中
        if (inputManager.getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_UP) {
            releasedLeftButtonUntilSwingEnded = true;
        }
        batter.nextFrame();
    }
    else {//スイング終了
        if ((inputManager.getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_DOWN) &&
            (releasedLeftButtonUntilSwingEnded == false)) {
            //OutputDebugString(L"スイング継続\n");
        }
        else {
            releasedLeftButtonUntilSwingEnded = true;
            batter.changeFrame(0);
            //OutputDebugString(L"スイング終了\n");
        }
    }
}

void PlayingState::updateBatterPos(const InputManager& inputManager)
{
    POINT nextKamayamaPos = { 0,0 };//次フレームの打者の座標

    //マウス座標を取得し、釜山の座標を変更
    const POINT mouse = inputManager.getMousePosition();
    Vector2D<float> velocityAngle(
        (float)(mouse.x - getCursorPos().x),
        (float)(mouse.y - getCursorPos().y));//速度ベクトル（向きしか意味を持たない）

    Batter& batter = gameObjectManager.getObject<Batter> ("BATTER");

    if (velocityAngle.norm() < batter.getSpeed()) {//ポインターとバッティングカーソルが近い
        nextKamayamaPos = { mouse.x - 302,mouse.y - 197 };
    }
    else {
        velocityAngle.normalize();
        velocityAngle.scalar(batter.getSpeed());


        nextKamayamaPos = PlayingState::nextKamayamaPos(batter.getPosition(), velocityAngle);//次フレームの釜山の位置
    }
    
    batter.setObjectPosition(nextKamayamaPos);
}

const POINT PlayingState::getCursorPos()
{
    POINT batterPos = gameObjectManager.getObject<PictureObject>("BATTER").getPosition();
    POINT cursorPos = { batterPos.x+302,batterPos.y+197};
    return cursorPos;
}

void PlayingState::initializeStartTime()
{
    phaseStartTime = GetTickCount64();
}

int& PlayingState::getRestBalls()
{
    return restBalls;
}

Ball& PlayingState::getBall()
{
    return ball;
}

int& PlayingState::getDistance()
{
    return distance;
}

std::unordered_map<std::string, PictureObject&>& PlayingState::getFieldImages()
{
    return fieldImages;
}

Result& PlayingState::getResult()
{
    return result;
}

void PlayingState::setBatterInBox(POINT mousePos)
{
    PictureObject& batter = gameObjectManager.getObject<PictureObject>("BATTER");
    POINT pos;
    if (PtInRect(&batterBox, mousePos)) {
        //posがbatterBoxの中
        pos = {
            mousePos.x - 302,
            mousePos.y - 197
        };
        batter.setObjectPosition(pos);
        return;
    }
    //以下、posはbatterBoxの外
    LONG x = std::max<LONG>(std::min<LONG>(mousePos.x-302, batterBox.right), batterBox.left);
    LONG y = std::max<LONG>(std::min<LONG>(mousePos.y-197, batterBox.bottom), batterBox.top);
    batter.setObjectPosition({ x,y });
}

void PlayingState::updateWaitingPitchingTimer()
{
    ULONGLONG currentTime = GetTickCount64();
    waitingPitchingTimer = currentTime - phaseStartTime;
}



POINT PlayingState::nextKamayamaPos(POINT position, Vector2D<float> movement)
{
    POINT nextPos = { 0,0 };
    nextPos.x = std::max<int>(batterBox.left, std::min<int>(position.x + (int)std::round(movement.x), batterBox.right));
    nextPos.y = std::max<int>(batterBox.top, std::min<int>(position.y + (int)std::round(movement.y), batterBox.bottom));
    return nextPos;
}

void PlayingState::updatePitchingMotion()
{
    //ピッチャーが第0フレーム
}

Stage* PlayingState::getStage()
{
    return stage;
}

Stadium& PlayingState::getStadium()
{
    return *stadium;
}
