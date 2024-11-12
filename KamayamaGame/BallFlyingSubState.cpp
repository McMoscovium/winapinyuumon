#include "BallFlyingSubState.h"

#include "Game.h"
#include <cmath>
#include <numbers>
#include "WaitingPitchingSubState.h"
#include "AfterBallLandingSubState.h"

void BallFlyingSubState::updateBall(Ball& ball)
{
	//ballのメンバ変数を更新
	POINT currentBallPos = ball.getPosition();
	LONG movementX = -(LONG)round(std::sin(static_cast<double>(ball.getAngle()) * std::numbers::pi / 180) * ball.getVelocity());
	LONG movementY = -(LONG)round(std::cos(static_cast<double>(ball.getAngle()) * std::numbers::pi / 180) * ball.getVelocity());
	POINT nextBallPos = {
		currentBallPos.x + movementX,
		currentBallPos.y + movementY
	};
	ball.setPosition(nextBallPos);
	ball.sethVelocity(ball.getHVelocity() - ball.getGravity());
	ball.setHeight(ball.getHeight() + ball.getHVelocity());
}

void BallFlyingSubState::updateBallObjectPos(GameObject& ballObject, Ball& ball)
{
	ballObject.setObjectPosition({
		575-(LONG)std::round(ball.getRadius()*ballObject.getSizeRate()),
		360 - (LONG)std::round(ball.getHeight())
		});
}

void BallFlyingSubState::updateFieldPicture(Ball& ball)
{
	GameObject& field = owner.getGameObject(L"PICTURE_FIELD00");
	field.setObjectPosition({
		575-ball.getX(),
		360-ball.getY()
		});
}

BallFlyingSubState::BallFlyingSubState(PlayingState& owner):
	GameSubState(owner)
{
}

void BallFlyingSubState::update(Game& game)
{
	Ball& ball=owner.getBall();
	GameObject& ballObject = owner.getGameObject(L"PICTURE_BALL");
	GameObject& batter = owner.getGameObject(L"PICTURE_BATTER");
	GameObject& pitcher = owner.getGameObject(L"PICTURE_PITCHER");

	//ボールが着弾したら止める
	//将来的にはchangeSubState
	if(ball.getHeight()<1){
		owner.changeSubState(new AfterBallLandingSubState(owner));
		return;
	}
	//以下、ボールが着弾してない

	//ballのメンバ変数を計算
	updateBall(ball);
	//ボールのサイズを更新
	ballObject.changeSizeRate(
		(float)(3 * ball.getHeight() + 400) / 1000
	);
	//ボールの描画位置を更新
	updateBallObjectPos(ballObject, ball);
	//投手の位置を更新
	pitcher.setObjectPosition({
		-ball.getX() + 958+575,
		-ball.getY() + 236+360
	});
	//打者の位置を更新
	batter.setObjectPosition({
		-ball.getX() + 960+575,
		-ball.getY() + 764+360
		});
	//フィールドの描画位置を更新
	updateFieldPicture(ball);
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
	owner.getGameObject(L"PICTURE_SHADOW").setObjectPosition({ 570,360 });
	owner.getGameObject(L"PICTURE_SHADOW").changeSizeRate(0.4f);
	owner.getGameObject(L"PICTURE_FIELD00").appear();
}

void BallFlyingSubState::exit(Game& game)
{
	GameObject& field = owner.getGameObject(L"PICTURE_FIELD00");
	field.hide();
	owner.getGameObject(L"PICTURE_BALL").hide();
	owner.getGameObject(L"PICTURE_SHADOW").hide();
}
