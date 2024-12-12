#include "GameState/StatusState/StatusState.h"

#include "GameState/GameState.h"
#include "Game/Game.h"
#include "Game/InputManager.h"
#include "GameObject/GameObject.h"
#include "GameObject/HatimituMeterObject.h"
#include "GameObject/GameObjectManager.h"

#include "GameState/TitleScreenState/TitleScreenState.h"
#include "GameState/PlayingState/PlayingState.h"
#include <Windows.h>
#include "GameObject/PictureObject.h"

#include "Game/SaveData/SaveData.h"

#include "resource.h"

StatusState::StatusState(Game& game) :
	GameState<StatusState,
	GameSubState<StatusState>>(game),
	data(SaveData(game.getCurrentVersion())),
	neededPowerPoint(0),
	neededMeetPoint(0),
	neededSpeedPoint(0)
{
	HINSTANCE hInstance = game.getHInstance();

	OutputDebugString(L"�Z�[�u�f�[�^�ǂݍ��݊J�n�B\n");
	//�Z�[�u�f�[�^��ǂݍ���
	SaveDataManager saveDataManager;
	SaveData saveData(game.getCurrentVersion());
	saveDataManager.load(saveData,game.getCurrentVersion());

	OutputDebugString(L"�Z�[�u�f�[�^���烁���o�ϐ���ݒ�B\n");
	//�Z�[�u�f�[�^���烁���o�ϐ���ݒ�
	loadSaveData(saveData);

	OutputDebugString(L"�C���X�^���X�����B\n");
	//�C���X�^���X����
	PictureObject& back = gameObjectManager.addFront<PictureObject>("BACK", IDB_BITMAP46, hInstance, SIZE{ 1152,720 });
	HatimituMeterObject& powerMeter = gameObjectManager.addFront<HatimituMeterObject>("POWER_HATIMITUMETER", IDB_BITMAP23, hInstance, SIZE{ 28,26 }, data.getPower(), data.getPowerFilled());
	HatimituMeterObject& meetMeter = gameObjectManager.addFront<HatimituMeterObject>("MEET_HATIMITUMETER", IDB_BITMAP23, hInstance, SIZE{ 28,26 }, data.getMeet(), data.getMeetFilled());
	HatimituMeterObject& speedMeter = gameObjectManager.addFront<HatimituMeterObject>("SPEED_HATIMITUMETER", IDB_BITMAP23, hInstance, SIZE{ 28,26 }, data.getSpeed(), data.getSpeedFilled());
	PictureObject& powerUp = gameObjectManager.addFront<PictureObject>("POWER_UP", IDB_BITMAP49, hInstance, SIZE{50,62});
	PictureObject& powerDown = gameObjectManager.addFront<PictureObject>("POWER_DOWN", IDB_BITMAP47, hInstance, SIZE{93,66});
	PictureObject& meetUp = gameObjectManager.addFront<PictureObject>("MEET_UP", IDB_BITMAP49, hInstance, SIZE{ 50,62 });
	PictureObject& meetDown = gameObjectManager.addFront<PictureObject>("MEET_DOWN", IDB_BITMAP47, hInstance, SIZE{ 93,66 });
	PictureObject& speedUp = gameObjectManager.addFront<PictureObject>("SPEED_UP", IDB_BITMAP49, hInstance, SIZE{ 50,62 });
	PictureObject& speedDown = gameObjectManager.addFront<PictureObject>("SPEED_DOWN", IDB_BITMAP47, hInstance, SIZE{ 93,66 });
	PictureObject& kettei = gameObjectManager.addFront<PictureObject>("KETTEI", IDB_BITMAP51, hInstance, SIZE{ 110,60 });
	PictureObject& henkou = gameObjectManager.addFront<PictureObject>("HENKOU", IDB_BITMAP50, hInstance, SIZE{ 114,73 });
	PictureObject& taitoruhe = gameObjectManager.addFront<PictureObject>("TAITORUHE", IDB_BITMAP48, hInstance, SIZE{ 180,70 });

	TextObject& pointsText = gameObjectManager.addFront<TextObject>("POINTS", std::to_wstring(data.getScore()) + L"pt");
	TextObject& neededPowerPointStr = gameObjectManager.addFront<TextObject>("NEEDED_POWER", std::to_wstring(neededPowerPoint));
	TextObject& neededMeetPointStr = gameObjectManager.addFront<TextObject>("NEEDED_MEET", std::to_wstring(neededMeetPoint));
	TextObject& neededSpeedPointStr = gameObjectManager.addFront<TextObject>("NEEDED_SPEED", std::to_wstring(neededSpeedPoint));
	

	//�ʒu�ݒ�
	powerMeter.setObjectPosition({ 200,200 });
	meetMeter.setObjectPosition({ 200,276 });
	speedMeter.setObjectPosition({ 200,381 });
	powerUp.setObjectPosition({ 987,195 });
	meetUp.setObjectPosition({ 987,303 });
	speedUp.setObjectPosition({ 987,400 });
	powerDown.setObjectPosition({ 1052,200 });
	meetDown.setObjectPosition({ 1052,303 });
	speedDown.setObjectPosition({ 1052,400 });
	kettei.setObjectPosition({ 934,631 });
	henkou.setObjectPosition({ 993,508 });
	taitoruhe.setObjectPosition({ 38,619 });
	pointsText.setObjectPosition({ 690,42 });
	neededPowerPointStr.setObjectPosition({ 767,197 });
	neededMeetPointStr.setObjectPosition({ 767,293 });
	neededSpeedPointStr.setObjectPosition({ 767,385 });


	//�͂��݂��[�^�[�����ݒ�
	powerMeter.setValue(5);

	showAll();

	OutputDebugString(L"StatusState�̃C���X�^���X���쐬����܂���\n");
}

void StatusState::update(Game& game)
{
	InputManager& inputManager = game.getInputManager();

	
	

	//�^�C�g���{�^������
	PictureObject& taitoruhe = gameObjectManager.getObject<PictureObject>("TAITORUHE");
	if (inputManager.isClicked(taitoruhe)) {
		game.changeState(new TitleScreenState(game));
		return;
	}

	
	PictureObject& powerUp = gameObjectManager.getObject<PictureObject>("POWER_UP");
	PictureObject& powerDown = gameObjectManager.getObject<PictureObject>("POWER_DOWN");
	PictureObject& meetUp = gameObjectManager.getObject<PictureObject>("MEET_UP");
	PictureObject& meetDown = gameObjectManager.getObject<PictureObject>("MEET_DOWN");
	PictureObject& speedUp = gameObjectManager.getObject<PictureObject>("SPEED_UP");
	PictureObject& speedDown = gameObjectManager.getObject<PictureObject>("SPEED_DOWN");
	HatimituMeterObject& powerMeter = gameObjectManager.getObject<HatimituMeterObject>("POWER_HATIMITUMETER");
	HatimituMeterObject& meetMeter = gameObjectManager.getObject<HatimituMeterObject>("MEET_HATIMITUMETER");
	HatimituMeterObject& speedMeter = gameObjectManager.getObject<HatimituMeterObject>("SPEED_HATIMITUMETER");

	PictureObject& henkou = gameObjectManager.getObject<PictureObject>("KETTEI");


	TextObject& pointText = gameObjectManager.getObject<TextObject>("POINTS"); 
	TextObject& neededPowerStr = gameObjectManager.getObject<TextObject>("NEEDED_POWER");
	TextObject& neededMeetStr = gameObjectManager.getObject<TextObject>("NEEDED_MEET");
	TextObject& neededSpeedStr = gameObjectManager.getObject<TextObject>("NEEDED_SPEED");

	//�f�o�b�O�p
	if (inputManager.getKeyState(0x4D) == InputManager::KeyState::KEY_PRESSED) {
		//M�L�[�������ꂽ
		data.setScore(data.getScore() + 100000);
		pointText.setText(std::to_wstring(data.getScore()) + L"pt");
	}


	//�X�e�[�^�X�{�^��UP/DOWN����
	if (inputManager.isClicked(powerUp)) {
		if (data.getScore() < neededPowerPoint) {

		}
		else{
			if (data.getPower() < 30) {
				//���[�^�[�ɉ��Z
				powerMeter.addValue();
				//�Z�[�u�f�[�^�p�����o�ϐ��X�V
				if (data.getPower() == data.getPowerFilled()) {
					data.setScore(data.getScore() - neededPowerPoint);
				}
				data.setPower(powerMeter.getValue());
				data.setPowerFilled(powerMeter.getFilledValue());
				data.setScore(data.getScore() - neededPowerPoint);
				neededPowerPoint = data.getPower() * 1000;
				//�|�C���g�\���X�V
				pointText.setText(std::to_wstring(data.getScore()) + L"pt");
				neededPowerStr.setText(std::to_wstring(neededPowerPoint));
				//�ύX�{�^����������悤�ɂ���
				allowModify = true;

			}
			
			OutputDebugString(L"power added.\n");
		}
	}
	if (inputManager.isClicked(meetUp)) {
		if (data.getScore() < neededMeetPoint) {

		}
		else {
			if (data.getMeet() < 30) {
				meetMeter.addValue();
				if (data.getMeet() == data.getMeetFilled()) {
					data.setScore(data.getScore() - neededMeetPoint);
				}
				data.setMeet(meetMeter.getValue());
				data.setMeetFilled(meetMeter.getFilledValue());
				neededMeetPoint = data.getMeet() * 1000;
				pointText.setText(std::to_wstring(data.getScore()) + L"pt");
				neededMeetStr.setText(std::to_wstring(neededMeetPoint));

				//�ύX�{�^����������悤�ɂ���
				allowModify = true;
			}
			OutputDebugString(L"meet added.\n");
		}
	}
	if (inputManager.isClicked(speedUp)) {
		if (data.getScore() < neededSpeedPoint) {

		}
		else {
			if (data.getSpeed() < 30) {
				speedMeter.addValue();
				if (data.getSpeed() == data.getSpeedFilled()) {
					data.setScore(data.getScore() - neededSpeedPoint);
				}
				data.setSpeed(speedMeter.getValue());
				data.setSpeedFilled(speedMeter.getFilledValue());
				neededSpeedPoint = data.getSpeed() * 1000;
				pointText.setText(std::to_wstring(data.getScore()) + L"pt");
				neededSpeedStr.setText(std::to_wstring(neededSpeedPoint));

				//�ύX�{�^����������悤�ɂ���
				allowModify = true;
			}
			OutputDebugString(L"speed added.\n");
		}
	}
	if (inputManager.isClicked(powerDown)) {
		powerMeter.subtractValue();
		if (data.getPower() > 1) {
			data.setPower(data.getPower() - 1);
			//����{�^����������悤�ɂ���
			allowModify = true;
		}
	}
	if (inputManager.isClicked(meetDown)) {
		meetMeter.subtractValue();
		if (data.getMeet() > 1) {
			data.setMeet(data.getMeet() - 1);
			//�ύX�{�^����������悤�ɂ���
			allowModify = true;
		}
	}
	if (inputManager.isClicked(speedDown)) {
		speedMeter.subtractValue();
		if (data.getSpeed() > 1) {
			data.setSpeed(data.getSpeed() - 1);
			//�ύX�{�^����������悤�ɂ���
			allowModify = true;
		}
	}

	//�ύX�{�^���������ꂽ��ASaveData�ɋL�^����
	
	if (inputManager.isClicked(henkou) && allowModify) {
		SaveDataManager saveDataManager;
		saveDataManager.save(data);
		allowModify = false;
	}
}
