#include "TitleScreenState.h"



#include "Game.h"
#include "InputManager.h"
#include <Windows.h>

#include "GameObject.h"
#include "PlayingState.h"
#include "StatusState.h"
#include "TextObject.h"
#include "TintinPitcher.h"
#include "KamayamaBatter.h"
#include "TheHundredAcreWoodStadium.h"
#include "TintinStage.h"
#include "PictureObject.h"

#include <string>


TitleScreenState::TitleScreenState(Game& game) :
    GameState(game)
{
    gameObjectManager.addFront<PictureObject>("TITLE", L".//assets//�^�C�g�����2.bmp", SIZE{ 1152,720 });
    gameObjectManager.addFront<PictureObject>("START", L".//assets//�͂��߂�.bmp", SIZE{ 256,128 });
    gameObjectManager.addFront<PictureObject>("STATUS", L".//assets//�X�e�[�^�X.bmp", SIZE{ 256,128 });
    gameObjectManager.addFront<PictureObject>("GACHA", L".//assets//�K�`��.bmp", SIZE{ 256,128 });
    gameObjectManager.addFront<PictureObject>("QUIT", L".//assets//�����.bmp", SIZE{ 256,128 });
    gameObjectManager.addFront<PictureObject>("KAMAYAMA", L".//assets//�N�}�̊��R.bmp", SIZE{ 172,178 });

    showAll();

    //�eGameObject�̕`��ʒu��ݒ�@TODO
    gameObjectManager.getObject<PictureObject>("TITLE").setObjectPosition({ 0,0 });
    gameObjectManager.getObject<PictureObject>("KAMAYAMA").setObjectPosition({ 32,48 });
    gameObjectManager.getObject<PictureObject>("START").setObjectPosition({240,352});
    gameObjectManager.getObject<PictureObject>("STATUS").setObjectPosition({ 576,352 });
    gameObjectManager.getObject<PictureObject>("GACHA").setObjectPosition({ 240,528 });
    gameObjectManager.getObject<PictureObject>("QUIT").setObjectPosition({ 576,528 });
}


void TitleScreenState::update(Game& game) {
    //�^�C�g����ʂ̍X�V����@TODO

    //�I���{�^���N���b�N��@TODO

    InputManager& inputManager = game.getInputManager();

    //�X�^�[�g�{�^���N���b�N��
    const PictureObject& startButton = gameObjectManager.getObject<PictureObject>("START");
    if (inputManager.isClicked(startButton)) {
        OutputDebugString(L"�X�^�[�g�{�^�����N���b�N���ꂽ\n");
        Stage* tintinStage = new TintinStage();
        game.changeState(new PlayingState(game, tintinStage));
        return;
    }
    //�X�e�[�^�X�{�^���N���b�N��
    const PictureObject& statusButton = gameObjectManager.getObject<PictureObject>("STATUS");
    if (inputManager.isClicked(statusButton)) {
        OutputDebugString(L"�X�e�[�^�X�{�^�����N���b�N���ꂽ\n");
        game.changeState(new StatusState(game));
        return;
    }
}