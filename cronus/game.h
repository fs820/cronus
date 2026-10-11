//--------------------------------------------
//
// ゲームメイン [game.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#include "scene.h"
#include "graphics_types.h"

class Sound;

constexpr const char* AMBIENT_FILE = "data/ambient.bin";
constexpr const char* CAMERA_FILE = "data/camera.bin";

//---------------------------------------------
// ゲームシーンクラス
//---------------------------------------------
class GameScene : public Scene
{
public:
    GameScene(Application* pApp) : Scene(pApp), m_ambient{}, m_pBgm{} {}
    virtual ~GameScene() override = default;

    void onEnter() override;
    void onExit() override;
    void onUpdate(float elapsedTime, float deltaTime) override;

private:
    Color m_ambient;
    std::unique_ptr<Sound> m_pBgm;
};
