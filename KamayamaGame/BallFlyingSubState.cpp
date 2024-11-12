#include "BallFlyingSubState.h"

#include "Game.h"

void BallFlyingSubState::updateBall(Ball& ball)
{
}

BallFlyingSubState::BallFlyingSubState(PlayingState& owner):
	GameSubState(owner)
{
}

void BallFlyingSubState::update(Game& game)
{
	Ball& ball=owner.getBall();
	//ボールの位置を計算
	updateBall(ball);
}

void BallFlyingSubState::enter(Game& game)
{
	owner.getGameObject(L"PICTURE_FIELD").hide();
	owner.getGameObject(L"PICTURE_BATTER").changeSizeRate(0.4f);
	owner.getGameObject(L"PICTURE_BATTER").setObjectPosition({ 484,490 });
	owner.getGameObject(L"BUTTON_EXIT").hide();
	owner.getGameObject(L"PICTURE_PITCHER").changeSizeRate(0.4f);
	owner.getGameObject(L"PICTURE_PITCHER").setObjectPosition({ 484,300 });
	owner.getGameObject(L"PICTURE_BALL").changeSizeRate(0.4f);
	owner.getGameObject(L"PICTURE_FIELD00").appear();
}

void BallFlyingSubState::exit(Game& game)
{
}
