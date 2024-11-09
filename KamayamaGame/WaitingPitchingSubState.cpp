#include "WaitingPitchingSubState.h"

#include <memory>
#include "InPitchingSubState.h"
#include "InputManager.h"
#include "Game.h"
#include "TitleScreenState.h"


using namespace std;

WaitingPitchingSubState::WaitingPitchingSubState(PlayingState& context) :GameSubState<PlayingState>(context)
{
    std::wstring message = L"WaitingPitchingSubState開始\n";
    OutputDebugString(message.c_str());
    //開始時刻を記録
    timer.recordTime();
}

void WaitingPitchingSubState::update()
{
    //タイマーの更新
    timer.update();
    //タイマーのチェック
    if (timer.span() > 5000) {//開始して5000ms経過
        //フェーズをIN_PITCHINGに変更
        context.changeSubState(make_unique<InPitchingSubState>(context));
        return;
    }

    Game& game = context.getGame();
    const InputManager& inputManager = game.getConstInputManager();

    //終了ボタンの処理
    GameObject& exitButton = context.getGameObject(L"BUTTON_EXIT");
    if (inputManager.isClicked(exitButton)) {
        game.changeState(make_unique<TitleScreenState>(game));
        return;
    }

    //以下、BUTTON_EXITクリック無し

    //バッターの位置を更新
    context.getBatter().updateBatterPos(inputManager);

    //スイングのアニメーション処理
    context.getBatter().updateSwingAnimation(inputManager);

    //打撃処理
    int currentBatterFrame = context.getBatter().getCurrentFrameNumber();
    if (2 <= currentBatterFrame && currentBatterFrame <= 4) {
        //context.getBoundingBox().appear();
        //context.getBatter().updateBatBoundingBox(currentBatterFrame);
    }

    if (currentBatterFrame >= 5) {
            //バット判定枠の消去
        context.getBoundingBox().hide();
    }
}

