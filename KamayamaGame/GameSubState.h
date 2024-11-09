#pragma once

template<typename Context>
class GameSubState
{
protected:
	Context& context;

public:
	GameSubState(Context& context) :context(context) {}
	virtual ~GameSubState() = default;

	virtual void update() = 0;
};