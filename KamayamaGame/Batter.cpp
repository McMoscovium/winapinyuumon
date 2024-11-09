#include "Batter.h"

#include <cmath>
#include "Vector2D.h"
#include "InputManager.h"
#include <memory>
#include "BatBoundingBox.h"
#include "Ball.h"
#include "PlayingState.h"

using namespace std;


Batter::Batter(LPCTSTR path, std::wstring objectName, SIZE frameSize, PlayingState& context) :
    GameObject(path, objectName, frameSize),
    batterBox({ 263,335,378,429 }),
    context(context)
{}

bool Batter::isHit(Ball ball)
{
    LONG diffX = abs(ball.getPositionX() - getPositionX());
    LONG diffY = abs(ball.getPositionY() - getPositionY());

    return diffX < 50 && diffY < 50;
}

POINT Batter::nextBatterPos(POINT position, Vector2D movement)
{
    POINT nextPos = {
        std::max<LONG>(batterBox.left,std::min<LONG>(position.x + (LONG)std::round(movement.x),batterBox.right)),
        std::max<LONG>(batterBox.top, std::min<LONG>(position.y + (LONG)std::round(movement.y), batterBox.bottom))
    };
    return nextPos;
}

void Batter::updateBatterPos(const InputManager& inputManager)
{
    POINT nextPos = { 0,0 };
    //マウス座標を取得し、釜山の座標を変更
    POINT mouse = inputManager.getMousePosition();

    Vector2D diff(
        static_cast<float>(mouse.x - cursorPos().x),
        static_cast<float>(mouse.y - cursorPos().y)
    );//カーソルからみたポインタのベクトル
    if (diff.norm() < moveSpeed) {//ポインターとバッティングカーソルが近い
        nextPos = { mouse.x - 302,mouse.y - 197 };
        setPosition(nextPos);
        return;
    }

    diff.normalize();
    diff.scalar((float)moveSpeed);
    nextPos = nextBatterPos(getPosition(), diff);//次フレームの釜山の位置
    setPosition(nextPos);
}

void Batter::updateSwingAnimation(const InputManager& inputManager)
{
    if (getCurrentFrameNumber() == 0) {
        if (inputManager.getKeyState(VK_LBUTTON) != InputManager::KeyState::KEY_PRESSED) {
            return;//何もしない
        }
        //以下、KEY_PRESSED
        releasedLeftButtonUntilSwingEnded = false;
        nextFrame();
        return;
    }

    if (getCurrentFrameNumber() > 0 && getCurrentFrameNumber() < length - 1) {
        if (inputManager.getKeyState(VK_LBUTTON) != InputManager::KeyState::KEY_DOWN) {
            releasedLeftButtonUntilSwingEnded = true;
        }
        nextFrame();
    }
    if (getCurrentFrameNumber() == length - 1) {//最終フレーム
        if (inputManager.getKeyState(VK_LBUTTON) != InputManager::KeyState::KEY_DOWN) {
            releasedLeftButtonUntilSwingEnded = true;
        }
        if (releasedLeftButtonUntilSwingEnded) {
            nextFrame();
        }
    }
}


void Batter::updateBatBoundingBox(int currentBatterFrame)
{
    //位置の設定
    POINT pos = { 300,500 + 50 * (currentBatterFrame - 3) };
    context.getBoundingBox().setPosition(pos);
}


POINT Batter::cursorPos()const
{
    POINT cursorPos = {
        getPosition().x + 302,
        getPosition().y + 197
    };
    return cursorPos;
}

LONG Batter::cursorX()
{
    return cursorPos().x;
}

LONG Batter::cursorY()
{
    return cursorPos().y;
}
