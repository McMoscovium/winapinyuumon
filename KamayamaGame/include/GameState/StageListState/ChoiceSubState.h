#pragma once

#include "GameState/GameSubState.h"
#include "GameState/TitleScreenState/TitleScreenState.h"
#include "GameState/StageListState/StageListState.h"
#include "GameState/StageListState/LoadResourceSubState.h"
#include "Stage/TintinStage.h"
#include "Stage/SasakiStage.h"
#include "Game/InputManager.h"

#include "Game/Game.h"

class ChoiceSubState :
	public GameSubState<StageListState>
{
private:
public:
	ChoiceSubState(StageListState& owner) :
		GameSubState(owner) {
	}
	~ChoiceSubState() = default;

	void enter(Game& game)override {

	}
	void update(Game& game)override {
		InputManager& inputManager = game.getInputManager();
		PictureObject& toTitleButton = gameObjectManager.getObject<PictureObject>("TO_TITLE");

		//タイトルヘボタン処理
		if (inputManager.isClicked(toTitleButton)) {
			game.changeState(new TitleScreenState(game));
			return;
		}

		PictureObject& stage1Button = gameObjectManager.getObject<PictureObject>("STAGE1");
		PictureObject& stage2Button = gameObjectManager.getObject<PictureObject>("STAGE2");

		//ステージ選択ボタン処理
		if (inputManager.isClicked(stage1Button)) {
			owner.changeSubState(new LoadResourceSubState(owner, new TintinStage()));
		}

		if (inputManager.isClicked(stage2Button)) {
			owner.changeSubState(new LoadResourceSubState(owner, new SasakiStage()));
		}
	}
	void exit(Game& game)override {}
};