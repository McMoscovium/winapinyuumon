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
			std::cerr << "currentState==null�ł�" << std::endl;
			return;
		}
		currentState->update();
	}

	/// <summary>
	/// nextState��currentState�ɂ���
	/// </summary>
	/// <returns>
	/// nextState!=null�Ȃ�true
	/// </returns>
	bool setNextState(StateBase<MachineType>* next) {
		//false�Ȃ�W�����b�e��
		bool ret = nextState == nullptr;
		nextState.reset(next);
		return ret;
	}
};