#pragma once

#include "Timer.h"

class Game;

template<typename StateType>
class GameSubState
{
public:
    // コンストラクタで所属するGameStateを受け取る
    GameSubState(StateType& ownerState) : owner(ownerState) {}
    virtual ~GameSubState() = default;

    virtual void update(Game& game) = 0;
    //changeSubStateで自動的に呼ばれる
    virtual void enter(Game& game) = 0;
    //changeSubStateで自動的に呼ばれる
    virtual void exit(Game& game) = 0;
protected:
    StateType& owner; // 所属するStateTypeへの参照
    Timer timer;
};