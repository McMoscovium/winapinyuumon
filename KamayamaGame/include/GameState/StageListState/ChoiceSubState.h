#pragma once

#include "GameState/GameSubState.h"
#include "GameState/TitleScreenState/TitleScreenState.h"
#include "GameState/StageListState/StageListState.h"
#include "GameState/StageListState/LoadResourceSubState.h"

#include "Stage/TintinStage.h"
#include "Stage/SasakiStage.h"

#include "Stage/EeyoreStage.h"
#include "Stage/LumpyStage.h"
#include "Stage/PigletStage.h"
#include "Stage/Kanga&RooStage.h"
#include "Stage/RabbitStage.h"
#include "Stage/OwlStage.h"
#include "Stage/TiggerStage.h"
#include "Stage/RobinStage.h"

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
			game.changeState(new TitleScreenState(game, owner.getAudioManager()));
			return;
		}

		//インスタンス取得
		PictureObject& stage1Button = gameObjectManager.getObject<PictureObject>("STAGE1");
		PictureObject& stage2Button = gameObjectManager.getObject<PictureObject>("STAGE2");
		PictureObject& stage3Button = gameObjectManager.getObject<PictureObject>("STAGE3");
		PictureObject& stage4Button = gameObjectManager.getObject<PictureObject>("STAGE4");
		PictureObject& stage5Button = gameObjectManager.getObject<PictureObject>("STAGE5");
		PictureObject& stage6Button = gameObjectManager.getObject<PictureObject>("STAGE6");
		PictureObject& stage7Button = gameObjectManager.getObject<PictureObject>("STAGE7");
		PictureObject& stage8Button = gameObjectManager.getObject<PictureObject>("STAGE8");

		//ステージ選択ボタン処理
		if (inputManager.isClicked(stage1Button)) {
			owner.changeSubState(new LoadResourceSubState(owner, new EeyoreStage()));
		}

		if (inputManager.isClicked(stage2Button)) {
			owner.changeSubState(new LoadResourceSubState(owner, new LumpyStage()));
		}

		if (inputManager.isClicked(stage3Button)) {
			owner.changeSubState(new LoadResourceSubState(owner, new PigletStage()));
		}

		if (inputManager.isClicked(stage4Button)) {
			owner.changeSubState(new LoadResourceSubState(owner, new KangaRooStage()));
		}

		if (inputManager.isClicked(stage5Button)) {
			owner.changeSubState(new LoadResourceSubState(owner, new RabbitStage()));
		}

		if (inputManager.isClicked(stage6Button)) {
			owner.changeSubState(new LoadResourceSubState(owner, new OwlStage()));
		}

		if (inputManager.isClicked(stage7Button)) {
			owner.changeSubState(new LoadResourceSubState(owner, new TiggerStage()));
		}

		if (inputManager.isClicked(stage8Button)) {
			owner.changeSubState(new LoadResourceSubState(owner, new RobinStage()));
		}
	}
	void exit(Game& game)override {}
};