#pragma once

#include "GameState.h"
#include <unordered_map>

class InputManager;
class GameObject;
class Game;

class TitleScreenState :
    public GameState
{
public:
    enum class ObjectName {
        PICTURE_TITLE,
        BUTTON_START,
        BUTTON_STATUS,
        BUTTON_GACHA,
        BUTTON_QUIT,
        PICTURE_BUSAN
    };
    TitleScreenState();
    ~TitleScreenState() {}
    void update(Game* game,InputManager* inputManager)override;//�X�^�[�g�{�^���������ꂽ��PlayingState�ɑJ��
private:
    std::unordered_map<ObjectName, GameObject*> gameObjects;//GameObject�Ƃ��̉摜��path�̃y�A
};