#include "BallFlyingSubState.h"

#include "Game.h"
#include <cmath>
#include <numbers>
#include "WaitingPitchingSubState.h"
#include "BattingResultSubState.h"
#include "Stadium.h"

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
	//座標更新
	int x = ball.getX();
	int y = ball.getY();
	//クソ実装@TODO
	gameObjectManager.getObject<PictureObject>("FIELD00").setObjectPosition({
		576-x,
		360-y
		});
	gameObjectManager.getObject<PictureObject>("FIELD01").setObjectPosition({
		576 - x,
		360 - 1200 - y
		});
	gameObjectManager.getObject<PictureObject>("FIELD02").setObjectPosition({
		576 - x,
		360 - 2400 - y
		});
	gameObjectManager.getObject<PictureObject>("FIELD10").setObjectPosition({
		576 + 1920 - x,
		360 - y
		});
	gameObjectManager.getObject<PictureObject>("FIELD11").setObjectPosition({
		576 + 1920 - x,
		360 - 1200 - y
		});
	gameObjectManager.getObject<PictureObject>("FIELD12").setObjectPosition({
		576 + 1920 - x,
		360 - 2400 - y
		});
	gameObjectManager.getObject<PictureObject>("FIELD-10").setObjectPosition({
		576 - 1920 - x,
		360 - y
		});
	gameObjectManager.getObject<PictureObject>("FIELD-11").setObjectPosition({
		576 - 1920 - x,
		360 - 1200 - y
		});
	gameObjectManager.getObject<PictureObject>("FIELD-12").setObjectPosition({
		576 - 1920 - x,
		360 - 2400 - y
		});
	
	//全部のフィールドを描画すると重いので、クライアント領域と重なるもののみ描画する
	Window* window = owner.getGame().getWindow();
	for (auto& [key, obj] : owner.getFieldImages()) {
		if (obj.isIntersectsWithClientRect(window)) {
			//クライアント領域と交わる
			obj.appear();
		}
		else {
			obj.hide();
		}
	}
}

void BallFlyingSubState::calculateDistance()
{
	POINT ballPos = owner.getBall().getPosition();
	POINT vector = {
		ballPos.x - 960,
		ballPos.y - 764
	};
	LONG r2 = vector.x * vector.x + vector.y * vector.y;
	owner.getDistance() = (int)std::sqrt(r2);
}

PlayingState::FlyBallResult BallFlyingSubState::determineResult(POINT ball)
{
	POINT origin = { 959,766 };//フィールド00.bmp上でのホームベースの位置
	POINT vector = {
		ball.x - origin.x,
		ball.y - origin.y
	};
	return owner.getStadium().result(vector);
}

BallFlyingSubState::BallFlyingSubState(PlayingState& owner):
	GameSubState(owner)
{
}

void BallFlyingSubState::update(Game& game)
{
	Ball& ball=owner.getBall();
	GameObject& ballObject = gameObjectManager.getObject<PictureObject>("BALL");
	GameObject& batter = gameObjectManager.getObject<PictureObject>("BATTER");
	GameObject& pitcher = gameObjectManager.getObject<PictureObject>("PITCHER");

	//ボールが着弾したら止める
	//将来的にはchangeSubState
	if(ball.getHeight()<1){
		//飛距離計算
		calculateDistance();
		//ホームランかファウルかヒットか
		POINT ballPos = ball.getPosition();
		PlayingState::FlyBallResult result = determineResult(ballPos);
		owner.changeSubState(new BattingResultSubState(owner, result));
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
	pitcher.appear();
	//打者の位置を更新
	batter.setObjectPosition({
		-ball.getX() + 960+575,
		-ball.getY() + 764+360
		});
	batter.appear();
	//フィールドの描画位置を更新
	updateFieldPicture(ball);
}

void BallFlyingSubState::enter(Game& game)
{
	gameObjectManager.getObject<PictureObject>("FIELD").hide();
	
	gameObjectManager.getObject<PictureObject>("EXIT").hide();
	gameObjectManager.getObject<PictureObject>("PITCHER").hide();
	gameObjectManager.getObject<PictureObject>("BATTER").hide();
	gameObjectManager.getObject<TextObject>("NORM").hide();
	gameObjectManager.getObject<TextObject>("RUNS").hide();
	gameObjectManager.getObject<TextObject>("REST").hide();


	gameObjectManager.getObject<PictureObject>("BATTER").changeSizeRate(0.4f);
	gameObjectManager.getObject<PictureObject>("PITCHER").changeSizeRate(0.4f);
	gameObjectManager.getObject<PictureObject>("BALL").changeSizeRate(0.4f);
	gameObjectManager.getObject<PictureObject>("BALLSHADOW").setObjectPosition({ 570,360 });
	gameObjectManager.getObject<PictureObject>("BALLSHADOW").changeSizeRate(0.4f);
	updateFieldPicture(owner.getBall());
}

void BallFlyingSubState::exit(Game& game)
{
	gameObjectManager.getObject<PictureObject>("BALL").hide();
	gameObjectManager.getObject<PictureObject>("BALLSHADOW").hide();
}
