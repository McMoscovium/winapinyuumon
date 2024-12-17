#pragma once

#include "GameState/PlayingState/PlayingState.h"
#include "Stage/Stage.h"
#include "GameState/StageListState/StageListState.h"
#include "GameState/GameSubState.h"
#include "Game/Game.h"
#include "resource.h"
#include "GameObject/TextObject.h"
#include "GameObject/PictureObject.h"
#include "GameObject/Pitcher/Pitcher.h"
#include "GameObject/Batter/Batter.h"
#include "Game/SaveData/SaveData.h"

#include <atomic>
#include <thread>



class LoadResourceSubState :
	public GameSubState<StageListState>
{
private:
	bool animationComplete;
	std::atomic<bool> loadingComplete;
	std::thread loadingThread;
	Stage* stage;
public:
	LoadResourceSubState(StageListState& owner, Stage* stage) :
		GameSubState(owner),
		loadingComplete(false),
		animationComplete(false),
		stage(stage)
	{}

	~LoadResourceSubState() {
		if (loadingThread.joinable()) {
			loadingThread.join();
		}
	}

	void update(Game& game)override {
		//���[�h�ƃA�j���[�V�����̗������I�������PlayingState��
		if (loadingComplete && animationComplete) {
			SaveData saveData(game.getCurrentVersion());
			SaveDataManager saveDataManager;
			saveDataManager.load(saveData, game.getCurrentVersion());
			game.changeState(new PlayingState(game, stage, saveData));
			return;
		}

		//���[�h�A�j���[�V�����̍X�V
		PictureObject& loadAnimation = gameObjectManager.getObject<PictureObject>("LOAD_ANIMATION");
		loadAnimation.nextFrame();
		if (loadAnimation.getCurrentFrameNumber() == loadAnimation.getLength()-1) {
			animationComplete = true;
		}
	}
	void enter(Game& game)override {
		//���[�h������ʃX���b�h�ŊJ�n
		
		//�ʃX���b�h���J���A���[�h�J�n
		loadingThread = std::thread(
			[this]() {
				Game& game = this->getOwner().getGame();
				//�܂��A�X�e�[�^�X���i�[����Ă���Z�[�u�f�[�^�����[�h
				Version version = game.getCurrentVersion();
				SaveDataManager saveDataManager;
				SaveData saveData(version);
				saveDataManager.load(saveData, version);
				loadResources(saveData);
				loadingComplete = true; // ���[�h������ʒm
			}
		);

		//���[�h�A�j���[�V�����̏o��
		PictureObject& loadAnimation = gameObjectManager.getObject<PictureObject>("LOAD_ANIMATION");
		loadAnimation.appear();
	}
	void exit(Game& game)override {}

	//PlayingState�̃��\�[�X��ǂݍ���
	void loadResources(const SaveData& saveData){
		HINSTANCE hInstance = owner.getGame().getHInstance();
		GameObjectManager& gameObjectManager = owner.getGameObjectManager();
		AudioManager& audioManager = owner.getAudioManager();
		Game& game = owner.getGame();

		//�t�B�[���h�摜�ǂݍ���
		gameObjectManager.addFront<PictureObject>("FIELD00", IDB_BITMAP25, hInstance, SIZE{ 1920,1200 });
		gameObjectManager.addFront<PictureObject>("FIELD01", IDB_BITMAP26, hInstance, SIZE{ 1920,1200 });
		gameObjectManager.addFront<PictureObject>("FIELD02", IDB_BITMAP27, hInstance, SIZE{ 1920,1200 });
		gameObjectManager.addFront<PictureObject>("FIELD10", IDB_BITMAP28, hInstance, SIZE{ 1920,1200 });
		gameObjectManager.addFront<PictureObject>("FIELD11", IDB_BITMAP30, hInstance, SIZE{ 1920,1200 });
		gameObjectManager.addFront<PictureObject>("FIELD12", IDB_BITMAP32, hInstance, SIZE{ 1920,1200 });
		gameObjectManager.addFront<PictureObject>("FIELD-10", IDB_BITMAP29, hInstance, SIZE{ 1920,1200 });
		gameObjectManager.addFront<PictureObject>("FIELD-11", IDB_BITMAP31, hInstance, SIZE{ 1920,1200 });
		gameObjectManager.addFront<PictureObject>("FIELD-12", IDB_BITMAP33, hInstance, SIZE{ 1920,1200 });

		//���̉摜���ǂݍ���
		gameObjectManager.addFront<PictureObject>("FIELD", IDB_BITMAP24, hInstance, SIZE{ 1152,720 });

		gameObjectManager.addFrontDirect<Pitcher>("PITCHER", stage->createPitcher(hInstance));
		gameObjectManager.addFrontDirect<Batter>("BATTER", stage->createBatter(hInstance, saveData));
		gameObjectManager.addFront<PictureObject>("EXIT", IDB_BITMAP6, hInstance, SIZE{ 256,128 });
		gameObjectManager.addFront<PictureObject>("BALL", IDB_BITMAP34, hInstance, SIZE{ 41,50 });
		gameObjectManager.addFront<PictureObject>("BALLSHADOW", IDB_BITMAP35, hInstance, SIZE{ 33,37 });
		gameObjectManager.addFront<PictureObject>("BAT_HITBOX", L".//assets//batHitBox.bmp", SIZE{ 50,50 });
		gameObjectManager.addFront<PictureObject>("FINISH", IDB_BITMAP12, hInstance, SIZE{ 680,158 });

		//�����Ńe�L�X�g�I�u�W�F�N�g�����Ƃ��܂���
		TextObject& normText = gameObjectManager.addFront<TextObject>("NORM", std::to_wstring(stage->getNorm()));
		TextObject& runsText = gameObjectManager.addFront<TextObject>("RUNS", std::to_wstring(0));
		TextObject& restText = gameObjectManager.addFront<TextObject>("REST", std::to_wstring(stage->getTrials()));
		gameObjectManager.addFront<TextObject>("DISTANCE", L"");
		gameObjectManager.addFront<TextObject>("RESULT", L"");

		//�J�b�g�C���p�摜
		gameObjectManager.addFront<PictureObject>("CUTIN", IDB_BITMAP44, game.getHInstance(), SIZE{ 2000,365 });
		gameObjectManager.addFront<PictureObject>("CUTIN_STRING", IDB_BITMAP45, game.getHInstance(), SIZE{ 1289,200 });

		//�eGameObject�̕`��ʒu��ݒ�
		gameObjectManager.getObject<PictureObject>("FIELD").setObjectPosition({ 0,0 });
		gameObjectManager.getObject<PictureObject>("BATTER").setObjectPosition({ 32,48 });
		gameObjectManager.getObject<PictureObject>("EXIT").setObjectPosition({ 850,500 });
		gameObjectManager.getObject<PictureObject>("PITCHER").setObjectPosition({ 514, 22 });
		normText.setObjectPosition({ 166,121 });
		runsText.setObjectPosition({ 192,198 });
		restText.setObjectPosition({ 160,259 });

		//�e�e�L�X�g��������
		std::wstring normString = std::to_wstring(stage->getNorm());
		gameObjectManager.getObject<TextObject>("NORM").setText(normString);
		gameObjectManager.getObject<TextObject>("NORM").setObjectPosition({ 229,125 });
		gameObjectManager.getObject<TextObject>("RUNS").setText(L"0");
		gameObjectManager.getObject<TextObject>("RUNS").setObjectPosition({ 229,188 });
		std::wstring restString = std::to_wstring(stage->getTrials());
		gameObjectManager.getObject<TextObject>("REST").setText(restString);
		gameObjectManager.getObject<TextObject>("REST").setObjectPosition({ 229,272 });

		//�I�[�f�B�I�t�@�C���̓ǂݍ���
		audioManager.addWav("BGM1", hInstance, IDR_WAVE3);
		audioManager.addWav("JUST", hInstance, IDR_WAVE2);
	}
};