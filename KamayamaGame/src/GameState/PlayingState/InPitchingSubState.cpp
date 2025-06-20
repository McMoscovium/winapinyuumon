#include "GameState/PlayingState/InPitchingSubState.h"


#include <Windows.h>

#include "Game/Game.h"
#include "Game/InputManager.h"
#include "GameObject/GameObject.h"
#include "GameObject/PictureObject.h"
#include "Game/Window.h"

#include "GameState/TitleScreenState/TitleScreenState.h"
#include "GameState/PlayingState/WaitingPitchingSubState.h"
#include "GameState/PlayingState/AfterMeetSubState.h"
#include "GameState/PlayingState/CutIn.h"
#include "GameState/PlayingState/BattingResultSubState.h"

#include "util/Vector2D.h"
#include <cmath>
#include <random>
#include "GameObject/Ball.h"
#include "GameObject/Batter/Batter.h"
#include "GameObject/Pitcher/Pitcher.h"


#include <typeinfo>

void InPitchingSubState::updatePitchingMotion()
{
    PictureObject& pitcher = gameObjectManager.getObject<PictureObject>("PITCHER");
    int frame = pitcher.getCurrentFrameNumber();
    if (frame < pitcher.getLength() - 1) {
        pitcher.nextFrame();
    }
    return;
}

void InPitchingSubState::updateBall()
{
    //インスタンスの取得
    Pitcher& pitcher = owner.getGameObjectManager().getObject<Pitcher>("PITCHER");
    Ball& ball = owner.getBall();
    
	//ボールの位置を更新
    POINT nextPos = ball.updatePitch(&pitcher);

    //見た目の更新
    PictureObject& ballObject = gameObjectManager.getObject<PictureObject>("BALL");
    PictureObject& shadow = gameObjectManager.getObject<PictureObject>("BALLSHADOW");
    if (ball.isVisible()) {
        ballObject.changeFrame(0);
        shadow.changeFrame(0);
    }
    else {
		ballObject.changeFrame(1);
        shadow.changeFrame(1);
    }
    //ボールと影のサイズを更新
    ballObject.changeSizeRate(
        (float)(1440 - (720 - ball.getY())) / (float)1440
    );
    shadow.changeSizeRate(
        (float)(1440 - (720 - ball.getY())) / (float)1440
    );
    //影とボールの位置を更新
    POINT shadowPos = {
        nextPos.x - (LONG)(17*shadow.getSizeRate()),
        nextPos.y
    };
    shadow.setObjectPosition(shadowPos);
    POINT objectPos = {
        //ボールの半径だけxざひょうをずらす
        nextPos.x - (LONG)std::round(
            ball.getRadius() * ballObject.getSizeRate()
        ),
        nextPos.y - (int)std::round(ball.getHeight()*ballObject.getSizeRate())
    };
    ballObject.setObjectPosition(objectPos);
}

bool InPitchingSubState::isMeet(GameObject& ballObject, Ball& ball, Batter& batter, int& hitStopTime)
{
    POINT cursorPos = owner.getCursorPos();
    POINT ballPos = ballObject.getPosition();

    if (abs(ballPos.y - cursorPos.y) > 50) {
        //カーソルとボールのY座標が遠い
        return false;
    }
    if (abs(ballPos.x+ball.getRadius() - cursorPos.x) > batter.getMeet()) {
        //カーソルとボールのX座標が遠い
        return false;
    }
    //以下、ボールとバットが当たった

    //ボールの速度データを計算
    //左右の角度
    float angle = (float)std::round((cursorPos.y - ballPos.y) * 1.8f);
    ball.setAngle(angle);

    //ジャストミートか計算
    int gap = abs(ballPos.x+ball.getRadius() - cursorPos.x);//ボールとカーソルのずれ具合
    hitStopTime = 150 - 30 * gap;
    if (hitStopTime < 50) { hitStopTime = 0; }

    //efficiencyの計算
    float evaluation = 0;//1に近いほどジャストミート
    evaluation = (batter.getMeet() - abs(ballPos.x + ball.getRadius() * ballObject.getSizeRate() - cursorPos.x)) / 60;
    float efficiency = min(1.5f, max(0.0f, evaluation));
    //上向きの早さを設定
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> dis(0.6f,0.1f);
    float hVelocity = (
        batter.getPower() * efficiency +
        ball.getVelocity() * (1.5f - efficiency) * 0.3f
        ) * std::max<float>(dis(gen), 0.1f);
    ball.sethVelocity(hVelocity);

    //水平の速さを設定
    int speed = (int)(batter.getPower() * ((efficiency + 0.6) / 2) * 1.08);
    if (hitStopTime > 0) {
        speed = (int)(speed * 1.3f);
    }
    ball.setVelocity(speed);

    OutputDebugString((L"hVelocity: " + std::to_wstring(hVelocity) + L"\n").c_str());
    OutputDebugString((L"velocity: " + std::to_wstring(speed) + L"\n").c_str());
    
    //最後にtrueを返す
    return true;
}

void InPitchingSubState::update(Game& game)
{
    Ball& ball = owner.getBall();
    PictureObject& ballObject = gameObjectManager.getObject<PictureObject>("BALL");
    PictureObject& shadow = gameObjectManager.getObject<PictureObject>("BALLSHADOW");
    Pitcher& pitcherObject = gameObjectManager.getObject<Pitcher>("PITCHER");
    
    
    //投げたボールが画面外まで行ったらchangeState
    if (!game.getWindow()->isInClientRect(ball.getPosition())) {
        ballObject.hide();
        shadow.hide();
        owner.changeSubState(new BattingResultSubState(owner, PlayingState::FlyBallResult::STRIKE));
        return;
    }

    //終了ボタン処理
    InputManager& inputManager = game.getInputManager();
    PictureObject& exitButton = gameObjectManager.getObject<PictureObject>("EXIT");
    if (inputManager.isClicked(exitButton)) {
        exit(game);//終了処理
        game.changeState(new TitleScreenState(game, owner.getAudioManager()));
        return;
    }

    //ボール座標の更新
    if (ballObject.isVisible() == true) {
        updateBall();
    }

    Pitcher& pitcher = owner.getGameObjectManager().getObject<Pitcher>("PITCHER");
    //ボール見た目の更新
    int frame = pitcherObject.getCurrentFrameNumber();
    if (frame == pitcher.releaseFrame) {//ボールをリリース
        POINT ballPos = ball.getPosition();
        ball.resetFrame();
        float sizeRate = (float)(1440 - (720 - ball.getY())) / (float)1440;
        ballObject.changeSizeRate(sizeRate);
        shadow.changeSizeRate(sizeRate);
        ballObject.setObjectPosition({
            ballPos.x - (LONG)std::round(sizeRate * ball.getRadius()),
            ballPos.y - (LONG)std::round(ball.getHeight() * sizeRate)
            });
        ballObject.appear();
        shadow.setObjectPosition({
            ballPos.x - (LONG)std::round(sizeRate * 17),
            ballPos.y
            });
        shadow.appear();
    }
    

    //ピッチングアニメーションの更新
    if (frame < pitcherObject.getLength() - 1) {
        pitcherObject.nextFrame();
    }
    
    //バッターの更新
    owner.updateBatterPos(inputManager);
    owner.updateBatterAnimation(inputManager);

    //打撃処理
    int currentBatterFrame = gameObjectManager.getObject<PictureObject>("BATTER").getCurrentFrameNumber();
    if (2 <= currentBatterFrame && currentBatterFrame <= 4) {
        //当たり判定が登場
        owner.updateBatFrame(currentBatterFrame);
        //ボールが当たったかどうかで分けて処理
        int hitStopTime = 0;
        Batter& batter = owner.getGameObjectManager().getObject<Batter>("BATTER");
        if (isMeet(ballObject, owner.getBall(), batter, hitStopTime)) {
            //影とボールを表示
            ballObject.changeFrame(0);
            shadow.changeFrame(0);

            if (hitStopTime&& abs(ball.getAngle()) < 44.9f) {
                //ミート音を鳴らす
                owner.getAudioManager().play("JUST", false);
                //ジャストミート
                owner.changeSubState(new CutIn(owner, hitStopTime));
                return;
            }
            //じゃすとみーとじゃない
            owner.changeSubState(new AfterMeetSubState(owner, hitStopTime));
            return;
        }
        return;
    }

    if (currentBatterFrame >= 5) {
        //バット判定枠の消去
        gameObjectManager.getObject<PictureObject>("BAT_HITBOX").hide();
    }
}

void InPitchingSubState::enter(Game& game)
{
    //ボールの初期位置
    Ball& ball = owner.getBall();
    ball.setHeight(70);
    ball.setPosition({ 542,115 });
    ball.sethVelocity(0);
    ball.setVelocity(0);

    //ボール出現
    ball.appear();

    //次の球種を決定
    Pitcher& pitcher = owner.getGameObjectManager().getObject<Pitcher>("PITCHER");
    pitcher.decideNextPitch();

    //決定した球種に従いボールの初期速度を設定
    
    ball.setVelocity(pitcher.getPitchingSpeed());
    ball.setAngle(pitcher.getPitchingAngle() + 180.0f);
    ball.sethVelocity(pitcher.getHVelocity());

    //残り球数を減らす
    owner.getRestBalls()--;
    
    OutputDebugString(L"Entering InPitchingState\n");
}

void InPitchingSubState::exit(Game& game)
{
    gameObjectManager.getObject<PictureObject>("BAT_HITBOX").hide();
    gameObjectManager.getObject<PictureObject>("PITCHER").changeFrame(0);//ピッチャーフレーム初期化
    OutputDebugString(L"Exitting InPitchingState\n");
}
