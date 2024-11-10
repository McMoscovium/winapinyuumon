#include "InPitchingSubState.h"

#include "Game.h"
#include "InputManager.h"
#include "GameObject.h"
#include "TitleScreenState.h"
#include "WaitingPitchingSubState.h"

void InPitchingSubState::updatePitchingMotion()
{
    GameObject& pitcher = owner.getGameObject(L"PICTURE_PITCHER");
    int frame = pitcher.getCurrentFrameNumber();
    if (frame < pitcher.getLength() - 1) {
        pitcher.nextFrame();
    }
    if (frame == 34) {//ボールをリリース
        owner.getGameObject(L"PICTURE_BALL").setObjectPosition({ 529,162 });
        owner.getGameObject(L"PICTURE_BALL").appear();
    }
    
    return;
}

void InPitchingSubState::updateBall()
{
    GameObject& ball = owner.getGameObject(L"PICTURE_BALL");
    //位置の更新
    const POINT formerPos = ball.getPosition();
    const POINT nextPos = {
        formerPos.x,
        formerPos.y + pitchingSpeed
    };
    ball.setObjectPosition(nextPos);

    //見た目の更新
    if (nextPos.y > 720) {
        ball.hide();
    }
}

void InPitchingSubState::update(Game& game)
{
    GameObject& ball = owner.getGameObject(L"PICTURE_BALL");

    if (ball.getPositionY() > 700) {//画面下に外れた
        ball.hide();
        owner.changeSubState(new WaitingPitchingSubState(owner));
        return;
    }

    InputManager& inputManager = game.getInputManager();
	//終了ボタン処理
    GameObject& exitButton = owner.getGameObject(L"BUTTON_EXIT");
    if (inputManager.isClicked(exitButton)) {
        exit(game);//終了処理
        game.changeState(new TitleScreenState(game));
        return;
    }

    //ピッチングアニメーションの更新
    updatePitchingMotion();
    //ボールの更新
    if (owner.getGameObject(L"PICTURE_BALL").isVisible() == true) {
        updateBall();
    }
    
    //バッターの更新
    owner.updateBatterPos(inputManager);
    owner.updateBatterAnimation(inputManager);

    //打撃処理
    int currentBatterFrame = owner.getGameObject(L"PICTURE_BATTER").getCurrentFrameNumber();
    if (2 <= currentBatterFrame && currentBatterFrame <= 4) {
        //当たり判定が登場
        owner.updateBatFrame(currentBatterFrame);
        //ボールが当たったかどうかで分けて処理
        return;
    }

    if (currentBatterFrame >= 5) {
        //バット判定枠の消去
        owner.getGameObject(L"JUDGE_BAT").hide();
    }
}

void InPitchingSubState::enter(Game& game)
{
    
    owner.getGameObject(L"PICTURE_BALL").setObjectPosition({ 529,162 });//ボール座標初期化
    OutputDebugString(L"Entering InPitchingState\n");
}

void InPitchingSubState::exit(Game& game)
{
    owner.getGameObject(L"PICTURE_PITCHER").changeFrame(0);//ピッチャーフレーム初期化
    OutputDebugString(L"Exitting InPitchingState\n");
}
