#include "InPitchingSubState.h"

#include "TitleScreenState.h"
#include "InputManager.h"
#include "Game.h"
#include "PlayingState.h"

using namespace std;

InPitchingSubState::InPitchingSubState(PlayingState& context):
    GameSubState(context)
{
    std::wstring message = L"InPitchingSubState開始\n";
    OutputDebugString(message.c_str());
}

void InPitchingSubState::update()
{
    //ピッチングアニメーションの更新
    updatePitchingMotion();
    
    //
    const InputManager& inputManager = context.getConstGame().getConstInputManager();

    //EXITボタンクリック時の処理
    {
        const GameObject& exitButton = context.getGameObject(L"BUTTON_EXIT");
        if (inputManager.isClicked(exitButton)) {
            context.getGame().changeState(make_unique<TitleScreenState>(context.getGame()));
            return;
        }
    }

    //以下、BUTTON_EXITクリック無し

    //バッターの位置をマウス位置に合わせて変更
    context.getBatter().updateBatterPos(inputManager);

    //スイングのアニメーション処理
    context.updateBatterAnimation(inputManager);

    int currentBatterFrame = context.getGameObject(L"PICTURE_BATTER").getCurrentFrameNumber();
    //打撃処理
    {
        if (2 <= currentBatterFrame && currentBatterFrame <= 4) {
            //context.getBatter().updateBatBoundingBox(currentBatterFrame);
        }


        if (currentBatterFrame >= 5) {
            //バット判定枠の消去
            context.getGameObject(L"BOX_BAT").hide();
        }

    }
}



void InPitchingSubState::updatePitchingMotion()
{
}
