#include "PlayingState.h"

#include "Game.h"
#include "GameSubState.h"
#include "GameOverState.h"
#include "InputManager.h"
#include "InPitchingSubState.h"
#include "WaitingPitchingSubState.h"
#include "Vector2D.h"
#include "TintinPitcher.h"
#include "TextObject.h"
#include "Batter.h"
#include "Stadium.h"

#include <algorithm>

#include"TitleScreenState.h"





PlayingState::PlayingState(Game& game, Batter* batter, Pitcher* pitcher, Stadium* stadium,int trials) :
    GameState(game),
    batter(batter),
    pitcher(pitcher),
    stadium(stadium),
    restBalls(trials)
{
    appendObject(L"PICTURE_FIELD00", L".//assets//フィールド00.bmp", { 1920,1200 });
    appendObject(L"PICTURE_FIELD01", L".//assets//フィールド01.bmp", { 1920,1200 });
    appendObject(L"PICTURE_FIELD02", L".//assets//フィールド02.bmp", { 1920,1200 });
    appendObject(L"PICTURE_FIELD10", L".//assets//フィールド10.bmp", { 1920,1200 });
    appendObject(L"PICTURE_FIELD11", L".//assets//フィールド11.bmp", { 1920,1200 });
    appendObject(L"PICTURE_FIELD12", L".//assets//フィールド12.bmp", { 1920,1200 });
    appendObject(L"PICTURE_FIELD-10", L".//assets//フィールド-10.bmp", { 1920,1200 });
    appendObject(L"PICTURE_FIELD-11", L".//assets//フィールド-11.bmp", { 1920,1200 });
    appendObject(L"PICTURE_FIELD-12", L".//assets//フィールド-12.bmp", { 1920,1200 });

    //フィールド画像だけここでまとめておく
    for (auto& [key, obj] : gameObjects) {
        fieldImages.emplace(key, *obj);
    }

    //GameObjectのインスタンスを生成
    appendObject(L"PICTURE_FIELD", L".//assets//フィールド.bmp", { 1152,720 });
    appendObject(L"PICTURE_SHADOW", L".//assets//ボールの影.bmp", { 33,37 });
    appendObject(L"PICTURE_BATTER", L".//assets//打者.bmp", { 360,391 });
    appendObject(L"BUTTON_EXIT", L".//assets//おわる.bmp", { 256,128 });
    appendObject(L"PICTURE_PITCHER", L".//assets//投手スプライトシート.bmp", { 168,266 });
    appendObject(L"PICTURE_BALL", L".//assets//ボール.bmp", { 41,50 });
    appendObject(L"JUDGE_BAT", L".//assets//battingJudgeFrame.bmp", { 50,50 });//バット当たり判定
    appendObject(L"PICTURE_FINISH", L".//assets//ゲーム終了.bmp", { 680,158 });


    gameObjects.emplace(L"TEXT_DISTANCE", new TextObject(L"TEXT_DISTANCE", L""));
    objectOrder.push_back(L"TEXT_DISTANCE");

    gameObjects.emplace(L"TEXT_RESULT", new TextObject(L"TEXT_RESULT", L""));
    objectOrder.push_back(L"TEXT_RESULT");
    

    //各GameObjectの描画位置を設定
    getGameObject(L"PICTURE_FIELD").setObjectPosition({ 0,0 });
    getGameObject(L"PICTURE_BATTER").setObjectPosition({ 32,48 });
    getGameObject(L"BUTTON_EXIT").setObjectPosition({ 850,500 });
    getGameObject(L"PICTURE_PITCHER").setObjectPosition({ 514, 22 });
    

    changeSubState(new WaitingPitchingSubState(*this));
}

PlayingState::~PlayingState()
{
    if (pitcher) {
        delete pitcher;
        pitcher = nullptr;
    }
    if (batter) {
        delete batter;
        batter = nullptr;
    }
}

void PlayingState::update(Game& game) {
    if (currentSubState)currentSubState->update(game);
}

void PlayingState::updateBatFrame(int currentBatterFrame)
{
    POINT batterPos = getGameObject(L"PICTURE_BATTER").getPosition();
    //バット判定枠移動
    POINT framePos = { getCursorPos().x - 25,
        getCursorPos().y - 25 - (currentBatterFrame - 3) * 25 };
    getGameObject(L"JUDGE_BAT").setObjectPosition(framePos);
    //バット判定枠の出現
    getGameObject(L"JUDGE_BAT").appear();
}




void PlayingState::updateBatterAnimation(const InputManager& inputManager)
{
    //釜山のスイング処理
    const int kamayamaFrame = getGameObject(L"PICTURE_BATTER").getCurrentFrameNumber();
    if (kamayamaFrame == 0) {//スイングしてない
        if (inputManager.getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_PRESSED) {
            releasedLeftButtonUntilSwingEnded = false;
            getGameObject(L"PICTURE_BATTER").nextFrame();
            //OutputDebugString(L"スイング開始\n");
        }
    }
    else if (kamayamaFrame < getGameObject(L"PICTURE_BATTER").getLength() - 1) {//スイング途中
        if (inputManager.getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_UP) {
            releasedLeftButtonUntilSwingEnded = true;
        }
        getGameObject(L"PICTURE_BATTER").nextFrame();
    }
    else {//スイング終了
        if ((inputManager.getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_DOWN) &&
            (releasedLeftButtonUntilSwingEnded == false)) {
            //OutputDebugString(L"スイング継続\n");
        }
        else {
            releasedLeftButtonUntilSwingEnded = true;
            getGameObject(L"PICTURE_BATTER").changeFrame(0);
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

    
    if (velocityAngle.norm() < getBatter()->getSpeed()) {//ポインターとバッティングカーソルが近い
        nextKamayamaPos = { mouse.x - 302,mouse.y - 197 };
    }
    else {
        velocityAngle.normalize();
        velocityAngle.scalar(getBatter()->getSpeed());


        nextKamayamaPos = PlayingState::nextKamayamaPos(getGameObject(L"PICTURE_BATTER").getPosition(), velocityAngle);//次フレームの釜山の位置
    }
    
    getGameObject(L"PICTURE_BATTER").setObjectPosition(nextKamayamaPos);
}

const POINT PlayingState::getCursorPos() const
{
    const POINT batterPos = getConstGameObject(L"PICTURE_BATTER").getPosition();
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

Batter* PlayingState::getBatter()
{
    return batter;
}

Pitcher* PlayingState::getPitcher()
{
    return pitcher;
}

Stadium* PlayingState::getStadium()
{
    return stadium;
}

int& PlayingState::getDistance()
{
    return distance;
}

std::unordered_map<std::wstring, GameObject&>& PlayingState::getFieldImages()
{
    return fieldImages;
}

Result& PlayingState::getResult()
{
    return result;
}

void PlayingState::setBatterInBox(POINT mousePos)
{
    POINT pos;
    if (PtInRect(&batterBox, mousePos)) {
        //posがbatterBoxの中
        pos = {
            mousePos.x - 302,
            mousePos.y - 197
        };
        getGameObject(L"PICTURE_BATTER").setObjectPosition(pos);
        return;
    }
    //以下、posはbatterBoxの外
    LONG x = std::max<LONG>(std::min<LONG>(mousePos.x-302, batterBox.right), batterBox.left);
    LONG y = std::max<LONG>(std::min<LONG>(mousePos.y-197, batterBox.bottom), batterBox.top);
    getGameObject(L"PICTURE_BATTER").setObjectPosition({ x,y });    
}

void PlayingState::updateWaitingPitchingTimer()
{
    ULONGLONG currentTime = GetTickCount64();
    waitingPitchingTimer = currentTime - phaseStartTime;
}


void PlayingState::hitting()
{
    POINT ballPos = getGameObject(L"PICTURE_BALL").getPosition();
    POINT batterPos = getGameObject(L"PICTURE_BATTER").getPosition();

    

    if (abs(ballPos.y - batterPos.y) < 50&&
        abs(ballPos.x - batterPos.x) < 50) {//ボールとバットが近い
        //バットとボールが当たった
        OutputDebugString(L"ヒット\n");

        //処理


        return;

    }
    OutputDebugStringW(L"空振り\n");
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
