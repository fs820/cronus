//--------------------------------------------
//
// タイトル [title.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "game.h"
#include "gui.h"
#include "mesh.h"
#include "application.h"
#include "texture.h"
#include "renderer.h"
#include "ground.h"
#include "mymath.h"

//-----------------------------
// 
// タイトルシーン
// 
//-----------------------------

//------------------------
// シーンに入るときの処理
//------------------------
void GameScene::onEnter()
{
    // アンチエイリアスとブルームを行う
    getApp()->getRenderer()->setPostProcessShaderMask(PostProcessShaderMask::FXAA | PostProcessShaderMask::Bloom);

    // アニメ調の色彩
    getApp()->getRenderer()->setToneMappingType(ToneMappingType::Anime);

    // 影の描画範囲
    getApp()->getRenderer()->setShadowMapArea(40.0f, 40.0f, 0.5f, 100.0f);

    // 環境光
    getApp()->getRenderer()->setAmbient(Color(0.2f, 0.2f, 0.2f, 1.0f));

    // Fog
    FogData fog{};
    fog.color = Color::White();
    fog.start = 800.0f;
    fog.end = 1100.0f;
    fog.horizonHeight = 0.0f;
    fog.skyFogHeight = 550.0f;
    fog.fogPower = 1.0f;
    fog.skyFogPower = 3.0f;
    getApp()->getRenderer()->setFog(fog);

    // 地面の生成
    auto pLogo = factory::createGround(*getApp()->getMeshManager(), getApp()->getTextureManager()->getTextureHandle(Hash("logo")), Transform(Vector3(0, 0, 0), Quaternion::RotationYawPitchRoll(0.0f, math::degreesToRadians(90.0f), 0.0f), Vector3(1000.0f, 1000.0f, 0)));
    getApp()->getSceneManager()->getActiveScene()->addGameObject(std::move(pLogo));
}

//------------------------
// シーンから出るときの処理
//------------------------
void GameScene::onExit()
{
}

//------------------------
// 更新処理
//------------------------
void GameScene::onUpdate(float elapsedTime, float deltaTime)
{
#ifdef _DEBUG
    if (ImGui::Begin("Game Scene")) // ウィンドウ開始
    {
        ImGui::Text("This is the Game Scene.");
    }
    ImGui::End(); // ウィンドウ終了
#endif // _DEBUG
}
