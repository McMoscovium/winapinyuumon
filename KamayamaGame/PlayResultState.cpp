#include "PlayResultState.h"
#include "CompareNormSubState.h"

PlayResultState::PlayResultState(Game& game, Result& result):
	GameState(game),
	result(result)
{
	//GameObject��݂���
	

	//substate������
	changeSubState(new CompareNormSubState(*this));
}

PlayResultState::~PlayResultState()
{
	//�|�C���^�^�̃����o��������delete
}

void PlayResultState::update(Game& game)
{
	if (currentSubState)currentSubState->update(game);
}
