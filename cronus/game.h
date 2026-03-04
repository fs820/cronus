//--------------------------------------------
//
// ゲームメイン [game.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#include "scene.h"

//---------------------------------------------
// ゲームシーンクラス
//---------------------------------------------
class GameScene : public Scene
{
public:
    GameScene(Application* pApp) : Scene(pApp) {}
    virtual ~GameScene() override = default;

    void onEnter() override;
    void onExit() override;
    void onUpdate(float elapsedTime, float deltaTime) override;

private:
};
