#pragma once

#include "StateBase.h"
#include <memory>
#include <iostream>


template <typename MachineType>
class StateMachine:
	public IStateMachine
{
protected:
	std::unique_ptr<StateBase<MachineType>> currentState;
	std::unique_ptr<StateBase<MachineType>> nextState;
public:
	StateMachine()
	virtual ~StateMachine() = default;

	void update() {
		if (nextState) {
			changeState();
		}
		if (currentState == nullptr) {
			std::cerr << "currentState==nullです" << std::endl;
			return;
		}
		currentState->update();
	}

	/// <summary>
	/// nextStateをcurrentStateにうつす
	/// </summary>
	/// <returns>
	/// nextState!=nullならtrue
	/// </returns>
	bool setNextState(StateBase<MachineType>* next) {
		//falseならジャムッテル
		bool ret = nextState == nullptr;
		nextState.reset(next);
		return ret;
	}
};