//--------------------------------------------
//
// タイトル [title.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#include "scene.h"

//---------------------------------------------
// タイトルシーンクラス
//---------------------------------------------
class TitleScene : public Scene
{
public:
    TitleScene() = default;
    ~TitleScene() override = default;
    void onEnter() override;
    void onExit() override;
    void update(float elapsedTime, float deltaTime) override;
    void render(const Renderer& renderer) override;

private:
};
