#pragma once

#include "GameState/PlayResultState/PlayResultState.h"


class Game;
class Result;

class DetailResultSubState :
	public GameSubState<PlayResultState>
{
private:
	const Result& result;
public:
	DetailResultSubState(PlayResultState& owner,const Result& result) :
		GameSubState(owner),
		result(result)
	{}
	~DetailResultSubState() = default;

	void update(Game& game)override;
	void enter(Game& game)override;
	void exit(Game& game)override;
};