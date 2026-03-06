//--------------------------------------------
//
// タイトル [title.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "game.h"
#include "gui.h"
#include "mesh.h"
#include "camera_comp.h"
#include "light_comp.h"
#include "application.h"
#include "texture.h"
#include "renderer.h"
#include "ground.h"
#include "mymath.h"
#include "binary_stream.h"
#include "player.h"
#include "model.h"

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
    auto pApp = getApp();                         // アプリケーション
    auto pRenderer = pApp->getRenderer();         // レンダラー

    // アンチエイリアスとブルームを行う
    pRenderer->setPostProcessShaderMask(PostProcessShaderMask::FXAA | PostProcessShaderMask::Bloom);

    // アニメ調の色彩
    pRenderer->setToneMappingType(ToneMappingType::Anime);

    // 影の解像度
    pRenderer->setShadowMapResolution(8192);

    // 影の描画範囲
    pRenderer->setShadowMapArea(40.0f, 40.0f, 0.5f, 100.0f);

    // 環境光
    BinaryReader reader(AMBIENT_FILE);
    if (reader.isValid()) m_ambient = reader.read<Color>();
    pRenderer->setAmbient(m_ambient);

    // Fog
    FogData fog{};
    fog.color = Color::White();
    fog.start = 800.0f;
    fog.end = 1100.0f;
    fog.horizonHeight = 0.0f;
    fog.skyFogHeight = 550.0f;
    fog.fogPower = 1.0f;
    fog.skyFogPower = 3.0f;
    pRenderer->setFog(fog);

    // カメラ
    Camera camera{};
    camera.SetPivot(Camera::Pivot::Target);
    camera.SetPivotPosition({ 0.0f, 1.5f, 0.0f }, true);
    camera.SetRadius(5.0f);
    camera.SetTheta(math::degreesToRadians(-90.0f));
    camera.SetPhi(math::degreesToRadians(45.0f));
    camera.SetFovY(math::degreesToRadians(55.0f));
    Vector2 screenMag{};
    pRenderer->getScreenSizeMagnification(screenMag);
    camera.SetAspectRatio(DEFAULT_SCREEN_SIZE.x * screenMag.x / DEFAULT_SCREEN_SIZE.y * screenMag.y);
    std::unique_ptr<GameObject> pCamera = std::make_unique<GameObject>();
    pCamera->Add<CameraComponent>(camera);
    addGameObject(std::move(pCamera));

    // ライト
    float distance = 60.0f;
    float lightTelta = math::degreesToRadians(135.0f);
    float lightPhi = math::degreesToRadians(30.0f);
    Vector3 targetPos = { 0, 0, 0 };
    Vector3 lightPos = Vector3::FromSpherical(distance, lightTelta, lightPhi);
    LightData light{};
    Vector3 lightDirVec = targetPos - lightPos;
    lightDirVec.normalize();
    light.position = { 0,0,0,0 };
    light.direction = { lightDirVec,0 };
    light.color = { 1,1,1,1 };
    std::unique_ptr<GameObject> pLight = std::make_unique<GameObject>();
    pLight->Add<LightComponent>(light, true, lightPos, targetPos, Vector3{ 0,1,0 });
    addGameObject(std::move(pLight));

    // 地面の生成
    auto pGround = factory::createGround(*getApp()->getMeshManager(), *getApp()->getTextureManager(), getApp()->getTextureManager()->getTextureHandle(Hash("ground")), Transform(Vector3(0, 0, 0), Quaternion::RotationYawPitchRoll(0.0f, math::degreesToRadians(90.0f), 0.0f), Vector3(10.0f, 10.0f, 0)), 1000.0f);
    addGameObject(std::move(pGround));

    // プレイヤーの生成
    auto pPlayer = factory::createPlayer(*getApp()->getModelManager(), *getApp()->getRenderer(), getApp()->getModelManager()->getModelHandle(Hash("player")), Transform(Vector3(0, 0, 0), Quaternion::RotationYawPitchRoll(0.0f, 0.0f, 0.0f), Vector3(1, 1, 1)), 100.0f);
    addGameObject(std::move(pPlayer));
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
    auto pApp = getApp();                         // アプリケーション
    auto pRenderer = pApp->getRenderer();         // レンダラー

    // 環境光
    pRenderer->setAmbient(m_ambient);

#ifdef _DEBUG
    if (ImGui::Begin("Game Scene")) // ウィンドウ開始
    {
        ImGui::Text("This is the Game Scene.");
    }
    ImGui::End(); // ウィンドウ終了

    // ImGuiで色を変える
    if (ImGui::Begin("Game Light"))
    {
        ImGui::ColorEdit4("Ambient", &m_ambient.r); // カラーエディット

        // ImGuiの編集が終了した
        if (ImGui::IsItemDeactivatedAfterEdit())
        {
            // 色を保存する
            BinaryWriter writer(AMBIENT_FILE);
            writer.write(m_ambient);
        }
    }
    ImGui::End();
#endif // _DEBUG
}
