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
			std::cerr << "currentState==null‚Å‚·" << std::endl;
			return;
		}
		currentState->update();
	}

	/// <summary>
	/// nextState‚ðcurrentState‚É‚¤‚Â‚·
	/// </summary>
	/// <returns>
	/// nextState!=null‚È‚çtrue
	/// </returns>
	bool setNextState(StateBase<MachineType>* next) {
		//false‚È‚çƒWƒƒƒ€ƒbƒeƒ‹
		bool ret = nextState == nullptr;
		nextState.reset(next);
		return ret;
	}
};