#pragma once

#include "util/Timer.h"
#include "GameObject/GameObjectManager.h"
#include <type_traits>
#include "IGameState.h"


class Game;

template<typename StateType>
class GameSubState
{
public:
    // コンストラクタで所属するGameStateを受け取る
    
    GameSubState(StateType& ownerState) :
        owner(ownerState),
        gameObjectManager(ownerState.getGameObjectManager())
    {}
    virtual ~GameSubState() = default;

    virtual void update(Game& game) = 0;
    //changeSubStateで自動的に呼ばれる
    virtual void enter(Game& game) = 0;
    //changeSubStateで自動的に呼ばれる
    virtual void exit(Game& game) = 0;
protected:
    StateType& owner; // 所属するStateTypeへの参照
    Timer timer;

    GameObjectManager& gameObjectManager;//親玉のおさがり
};