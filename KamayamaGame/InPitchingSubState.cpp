#include "InPitchingSubState.h"

#include "Game.h"
#include "InputManager.h"
#include "GameObject.h"
#include "TitleScreenState.h"

void InPitchingSubState::updatePitchingMotion()
{
}

void InPitchingSubState::update(Game& game)
{
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
    OutputDebugString(L"Entering InPitchingState\n");
}

void InPitchingSubState::exit(Game& game)
{
    OutputDebugString(L"Exitting InPitchingState\n");
}
