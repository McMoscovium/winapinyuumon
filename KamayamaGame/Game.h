#pragma once

/*
PC内部でのゲームの進行を管理するクラス。
仮想画面への描画も行う。
*/


#include <memory>
#include "AudioManager.h"
#include "InputManager.h"
#include "IGameState.h"

class Window;


class Game
{
private:
	std::unique_ptr<IGameState> currentState = nullptr;
	InputManager inputManager;
	AudioManager audioManager;

public:
	Game();
	~Game();

	//currentStateを変更する
	void changeState(std::unique_ptr<IGameState> newState) {
		currentState = std::move(newState);
	}

	//終了処理
	void termination();

	//const版のゲッター
	const InputManager& getConstInputManager()const;
	//mutable版のゲッタ―
	InputManager& getInputManager();
	//
	const std::unique_ptr<IGameState>& getCurrentState()const;
};