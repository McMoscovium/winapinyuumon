#include "BallFlyingSubState.h"

#include "Game.h"
#include <cmath>
#include <numbers>
#include "WaitingPitchingSubState.h"
#include "AfterBallLandingSubState.h"

void BallFlyingSubState::updateBall(Ball& ball)
{
	//ball�̃����o�ϐ����X�V
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
	//���W�X�V
	int x = ball.getX();
	int y = ball.getY();
	//�N�\����@TODO
	owner.getGameObject(L"PICTURE_FIELD00").setObjectPosition({
		576-x,
		360-y
		});
	owner.getGameObject(L"PICTURE_FIELD01").setObjectPosition({
		576 - x,
		360 - 1200 - y
		});
	owner.getGameObject(L"PICTURE_FIELD02").setObjectPosition({
		576 - x,
		360 - 2400 - y
		});
	owner.getGameObject(L"PICTURE_FIELD10").setObjectPosition({
		576 + 1920 - x,
		360 - y
		});
	owner.getGameObject(L"PICTURE_FIELD11").setObjectPosition({
		576 + 1920 - x,
		360 - 1200 - y
		});
	owner.getGameObject(L"PICTURE_FIELD12").setObjectPosition({
		576 + 1920 - x,
		360 - 2400 - y
		});
	owner.getGameObject(L"PICTURE_FIELD-10").setObjectPosition({
		576 - 1920 - x,
		360 - y
		});
	owner.getGameObject(L"PICTURE_FIELD-11").setObjectPosition({
		576 - 1920 - x,
		360 - 1200 - y
		});
	owner.getGameObject(L"PICTURE_FIELD-12").setObjectPosition({
		576 - 1920 - x,
		360 - 2400 - y
		});
	
	//�S���̃t�B�[���h��`�悷��Əd���̂ŁA�N���C�A���g�̈�Əd�Ȃ���̂̂ݕ`�悷��
	Window* window = owner.getGame().getWindow();
	for (auto& [key, obj] : owner.getFieldImages()) {
		if (obj.isIntersectsWithClientRect(window)) {
			//�N���C�A���g�̈�ƌ����
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

	//�{�[�������e������~�߂�
	//�����I�ɂ�changeSubState
	if(ball.getHeight()<1){
		//�򋗗��v�Z
		calculateDistance();
		owner.changeSubState(new AfterBallLandingSubState(owner));
		return;
	}
	//�ȉ��A�{�[�������e���ĂȂ�

	//ball�̃����o�ϐ����v�Z
	updateBall(ball);
	//�{�[���̃T�C�Y���X�V
	ballObject.changeSizeRate(
		(float)(3 * ball.getHeight() + 400) / 1000
	);
	//�{�[���̕`��ʒu���X�V
	updateBallObjectPos(ballObject, ball);
	//����̈ʒu���X�V
	pitcher.setObjectPosition({
		-ball.getX() + 958+575,
		-ball.getY() + 236+360
	});
	pitcher.appear();
	//�Ŏ҂̈ʒu���X�V
	batter.setObjectPosition({
		-ball.getX() + 960+575,
		-ball.getY() + 764+360
		});
	batter.appear();
	//�t�B�[���h�̕`��ʒu���X�V
	updateFieldPicture(ball);
}

void BallFlyingSubState::enter(Game& game)
{
	owner.getGameObject(L"PICTURE_FIELD").hide();
	
	owner.getGameObject(L"BUTTON_EXIT").hide();
	owner.getGameObject(L"PICTURE_PITCHER").hide();
	owner.getGameObject(L"PICTURE_BATTER").hide();
	owner.getGameObject(L"PICTURE_BATTER").changeSizeRate(0.4f);
	owner.getGameObject(L"PICTURE_PITCHER").changeSizeRate(0.4f);
	owner.getGameObject(L"PICTURE_BALL").changeSizeRate(0.4f);
	owner.getGameObject(L"PICTURE_SHADOW").setObjectPosition({ 570,360 });
	owner.getGameObject(L"PICTURE_SHADOW").changeSizeRate(0.4f);
	updateFieldPicture(owner.getBall());
}

void BallFlyingSubState::exit(Game& game)
{
	owner.getGameObject(L"PICTURE_BALL").hide();
	owner.getGameObject(L"PICTURE_SHADOW").hide();
}
