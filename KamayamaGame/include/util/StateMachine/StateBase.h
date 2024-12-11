#pragma once

template <typename MachineType>
class StateBase
{
protected:
	MachineType& machine;
public:
	StateBase(MachineType& machine):
		machine(machine){ }
	virtual ~StateBase() = default;

	virtual void enter() = 0;
	virtual void update() = 0;
	virtual void exit() = 0;
};