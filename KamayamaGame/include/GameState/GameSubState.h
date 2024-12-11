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
    // �R���X�g���N�^�ŏ�������GameState���󂯎��
    
    GameSubState(StateType& ownerState) :
        owner(ownerState),
        gameObjectManager(ownerState.getGameObjectManager())
    {}
    virtual ~GameSubState() = default;

    virtual void update(Game& game) = 0;
    //changeSubState�Ŏ����I�ɌĂ΂��
    virtual void enter(Game& game) = 0;
    //changeSubState�Ŏ����I�ɌĂ΂��
    virtual void exit(Game& game) = 0;
protected:
    StateType& owner; // ��������StateType�ւ̎Q��
    Timer timer;

    GameObjectManager& gameObjectManager;//�e�ʂ̂�������
};