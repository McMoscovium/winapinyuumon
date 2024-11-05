#include "PlayingState.h"

#include "Game.h"
#include "GameOverState.h"
#include "InputManager.h"

#include <algorithm>

#include"TitleScreenState.h"


class Vector2D {
public:
    Vector2D(float x, float y) :x(x), y(y) {}
    float x;
    float y;
    float norm()const {
        return sqrt(x * x + y * y);
    }
    void normalize() {
        if (norm() == 0) {
            return;
        }
        float r = norm();
        x = x / r;
        y = y / r;
    }
    void scalar(float r) {
        x = r * x;
        y = r * y;
    }
};


PlayingState::PlayingState()
{
    //GameObjectのインスタンスを生成
    appendObject(L"PICTURE_FIELD", L".//assets//フィールド.bmp", { 1152,720 });
    appendObject(L"PICTURE_BATTER", L".//assets//打者.bmp", { 360,391 });
    appendObject(L"BUTTON_EXIT", L".//assets//おわる.bmp", { 256,128 });
    appendObject(L"PICTURE_PITCHER", L".//assets//投手.bmp", { 112,182 });
    appendObject(L"PICTURE_BALL", L".//assets//ボール.bmp", { 41,50 });
    appendObject(L"JUDGE_BAT", L".//assets//battingJudgeFrame.bmp", { 50,50 });//バット当たり判定

    gameObjects.at(L"JUDGE_BAT")->hide();

    //各GameObjectの描画位置を設定
    gameObjects.at(L"PICTURE_FIELD")->setObjectPosition({ 0,0 });
    gameObjects.at(L"PICTURE_BATTER")->setObjectPosition({ 32,48 });
    gameObjects.at(L"BUTTON_EXIT")->setObjectPosition({ 850,500 });
    gameObjects.at(L"PICTURE_PITCHER")->setObjectPosition({ 514, 22 });
    
    initializeStartTime();

    OutputDebugString(L"PlayingStateのインスタンスが作成されました\n");
}


void PlayingState::update(Game* game, InputManager* inputManager) {
    switch (phase) {
    case WAITING_PITCHING:
        updateWaitingPitchingPhase(inputManager, game);
        break;
    case IN_PITCHING:
        updateInPitchingPhase(inputManager, game);
    }
    
}

void PlayingState::updateWaitingPitchingPhase(InputManager* inputManager, Game* game)
{
    //タイマーの更新
    updateWaitingPitchingTimer();
    //タイマーのチェック
    if (waitingPitchingTimer > 5000) {
        //フェーズをIN_PITCHINGに変更
        changePhase(IN_PITCHING);
        return;
    }

    //ヒッティングカーソルの位置を更新
    updateCursorPos(inputManager);

    //プレイ中の更新処理

    if (isClicked(L"BUTTON_EXIT", inputManager)) {
        game->changeState(new TitleScreenState());
        return;
    }

    //以下、BUTTON_EXITクリック無し

    //バッターの位置をマウス位置に合わせて変更
    updateBatterPos(inputManager);

    //スイングのアニメーション処理
    updateBatterAnimation(inputManager);


    int currentBatterFrame = gameObjects.at(L"PICTURE_BATTER")->getCurrentFrameNumber();
    //打撃処理
    {
        if (2 <= currentBatterFrame && currentBatterFrame <= 4) {
            updateBatFrame(currentBatterFrame);
            hitting();
        }


        if (currentBatterFrame >= 5) {
            //バット判定枠の消去
            gameObjects.at(L"JUDGE_BAT")->hide();
        }

    }
}

void PlayingState::updateBatFrame(int currentBatterFrame)
{
    POINT batterPos = gameObjects.at(L"PICTURE_BATTER")->getPosition();
    //バット判定枠移動
    POINT framePos = { getCursorPos().x - 25,
        getCursorPos().y - 25 - (currentBatterFrame - 3) * 25 };
    gameObjects.at(L"JUDGE_BAT")->setObjectPosition(framePos);
    //バット判定枠の出現
    gameObjects.at(L"JUDGE_BAT")->appear();
}

void PlayingState::updateInPitchingPhase(InputManager* inputManager, Game* game)
{
    //ヒッティングカーソルの位置を更新
    updateCursorPos(inputManager);

    //プレイ中の更新処理

    if (isClicked(L"BUTTON_EXIT", inputManager)) {
        game->changeState(new TitleScreenState());
        return;
    }

    //以下、BUTTON_EXITクリック無し

    //バッターの位置をマウス位置に合わせて変更
    updateBatterPos(inputManager);

    //スイングのアニメーション処理
    updateBatterAnimation(inputManager);


    int currentBatterFrame = gameObjects.at(L"PICTURE_BATTER")->getCurrentFrameNumber();
    //打撃処理
    {
        if (2 <= currentBatterFrame && currentBatterFrame <= 4) {
            updateBatFrame(currentBatterFrame);
            hitting();
        }


        if (currentBatterFrame >= 5) {
            //バット判定枠の消去
            gameObjects.at(L"JUDGE_BAT")->hide();
        }

    }
}

void PlayingState::updateCursorPos(InputManager* inputManager)
{
    cursorPos = { gameObjects.at(L"PICTURE_BATTER")->getPositionX() + 302,
    gameObjects.at(L"PICTURE_BATTER")->getPositionY() + 197};
}

void PlayingState::updateBatterAnimation(InputManager* inputManager)
{
    //釜山のスイング処理
    const int kamayamaFrame = gameObjects.at(L"PICTURE_BATTER")->getCurrentFrameNumber();
    if (kamayamaFrame == 0) {//スイングしてない
        if (inputManager->getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_PRESSED) {
            releasedLeftButtonUntilSwingEnded = false;
            gameObjects.at(L"PICTURE_BATTER")->nextFrame();
            //OutputDebugString(L"スイング開始\n");
        }
    }
    else if (kamayamaFrame < gameObjects.at(L"PICTURE_BATTER")->getLength() - 1) {//スイング途中
        if (inputManager->getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_UP) {
            releasedLeftButtonUntilSwingEnded = true;
        }
        gameObjects.at(L"PICTURE_BATTER")->nextFrame();
    }
    else {//スイング終了
        if ((inputManager->getKeyState(VK_LBUTTON) == InputManager::KeyState::KEY_DOWN) &&
            (releasedLeftButtonUntilSwingEnded == false)) {
            //OutputDebugString(L"スイング継続\n");
        }
        else {
            releasedLeftButtonUntilSwingEnded = true;
            gameObjects.at(L"PICTURE_BATTER")->changeFrame(0);
            //OutputDebugString(L"スイング終了\n");
        }
    }
}

void PlayingState::updateBatterPos(InputManager* inputManager)
{
    POINT nextKamayamaPos = { 0,0 };//次フレームの打者の座標

    //マウス座標を取得し、釜山の座標を変更
    POINT mouse = inputManager->getMousePosition();
    Vector2D velocityAngle(mouse.x - getCursorPos().x,
        mouse.y - getCursorPos().y);//速度ベクトル（向きしか意味を持たない）


    
    if (velocityAngle.norm() < batterMovementSpeed) {//ポインターとバッティングカーソルが近い
        nextKamayamaPos = { mouse.x - 302,mouse.y - 197 };
    }
    else {
        velocityAngle.normalize();
        velocityAngle.scalar((float)batterMovementSpeed);


        nextKamayamaPos = PlayingState::nextKamayamaPos(gameObjects.at(L"PICTURE_BATTER")->getPosition(), velocityAngle);//次フレームの釜山の位置
    }
    
    std::wstring message = L"x: " + std::to_wstring(nextKamayamaPos.x) + L" y: " + std::to_wstring(nextKamayamaPos.y) + L"\n";

    OutputDebugString(message.c_str());
    
    gameObjects[L"PICTURE_BATTER"]->setObjectPosition(nextKamayamaPos);
}

const POINT PlayingState::getCursorPos() const
{
    return cursorPos;
}

void PlayingState::initializeStartTime()
{
    phaseStartTime = GetTickCount64();
}

void PlayingState::updateWaitingPitchingTimer()
{
    DWORD currentTime = GetTickCount64();
    waitingPitchingTimer = currentTime - phaseStartTime;
}

void PlayingState::changePhase(Phase phase)
{
    PlayingState::phase = phase;
}

void PlayingState::hitting()
{
    POINT ballPos = gameObjects.at(L"PICTURE_BALL")->getPosition();
    POINT batterPos = gameObjects.at(L"PICTURE_BATTER")->getPosition();

    

    if (abs(ballPos.y - batterPos.y) < 50&&
        abs(ballPos.x - batterPos.x) < 50) {//ボールとバットが近い
        //バットとボールが当たった
        OutputDebugString(L"ヒット\n");

        //処理


        return;

    }
    OutputDebugStringW(L"空振り\n");
}

POINT PlayingState::nextKamayamaPos(POINT position, Vector2D movement)
{
    POINT nextPos = { 0,0 };
    nextPos.x = std::max<int>(batterBox.left, std::min<int>(position.x + (int)std::round(movement.x), batterBox.right));
    nextPos.y = std::max<int>(batterBox.top, std::min<int>(position.y + (int)std::round(movement.y), batterBox.bottom));
    return nextPos;
}
