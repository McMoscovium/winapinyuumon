#pragma once

#include <unordered_map>
#include <string>
#include "GameObject.h"
#include <vector>

class Game;

class IGameState
{
protected:
    Game& game;//親玉
    std::unordered_map<std::wstring, GameObject*> gameObjects = {};//GameObjectの列（画面奥から順）
    std::vector<std::wstring> objectOrder = {};//オブジェクト名を描画順込みで並べたもの
public:
    IGameState(Game& game);
    virtual ~IGameState();
    virtual void update(Game& game) = 0;
    //objectOrderのゲッタ
    const std::vector<std::wstring>& getObjectOrder()const;
    //指定した名前のゲームオブジェクトのゲッタ
    GameObject& getGameObject(std::wstring objectName);
    //
    GameObject* getGameObjectPtr(std::wstring objectName);
    //
    const GameObject& getConstGameObject(std::wstring objectName)const;
    //ゲームオブジェクトを追加
    void appendObject(std::wstring objectName, LPCTSTR path, SIZE frameSize);
    //ゲームオブジェクトを直接追加
    void appendObject(GameObject* object);
    //オブジェクトの個数
    const unsigned int numberOfObjects()const;
    //
    void showAll();
    Game& getGame();
};

