#include "PlayResultState.h"
#include "CompareNormSubState.h"

PlayResultState::PlayResultState(Game& game, Result& result):
	GameState(game),
	result(result)
{
	//GameObjectよみこみ
	

	//substate初期化
	changeSubState(new CompareNormSubState(*this));
}

PlayResultState::~PlayResultState()
{
	//ポインタ型のメンバがいたらdelete
}

void PlayResultState::update(Game& game)
{
	if (currentSubState)currentSubState->update(game);
}
