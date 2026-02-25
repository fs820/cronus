//--------------------------------------------
//
// シーン [scene.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "scene.h"
#include "object.h"
#include "camera.h"

//---------------------------------------------
// 
// シーン管理クラス
// 
//---------------------------------------------

//------------------
// シーンを追加
//------------------
void SceneManager::addScene(std::string_view sceneName, Scene* scene)
{
    m_scenes.try_emplace(std::string(sceneName), std::unique_ptr<Scene>(scene)); // シーンを追加
}

//------------------
// シーンを切り替える
//------------------
void SceneManager::changeScene(std::string_view sceneName)
{
    auto it = m_scenes.find(std::string(sceneName));
    if (it != m_scenes.end())
    {
        if (m_activeScene != nullptr)
        {
            m_activeScene->onExit(); // 現在のシーンから出る
        }
        m_activeScene = it->second.get();
        m_activeScene->onEnter(); // 新しいシーンに入る
    }
}

//------------------
// シーンの更新
//------------------
void SceneManager::update(float elapsedTime, float deltaTime)
{
    // シーンの更新
    if (m_activeScene != nullptr)
    {
        m_activeScene->update(elapsedTime, deltaTime);
    }
}

//---------------------------------------------
//
// シーンクラス
//
//---------------------------------------------
Scene::Scene() = default;
Scene::~Scene() = default;

//------------------
// 更新
//------------------
void Scene::update(float elapsedTime, float deltaTime)
{
    if (m_camera == nullptr) m_camera = std::make_unique<Camera>(); // カメラの生成
    m_camera->Set(); // カメラの設定

    // StartしていないゲームオブジェクトのStartを呼び出す
    for (auto& gameObject : m_noStartObjects)
    {
        if (!gameObject->Start())
        {
            gameObject->markForDestroy(); // Startに失敗したゲームオブジェクトは破棄予定にする
        }
    }
    m_noStartObjects.clear(); // Startしていないゲームオブジェクトのリストをクリア

    // ゲームオブジェクトの更新
    for (auto& gameObject : m_gameObjects)
    {
        gameObject->Update(deltaTime);
    }

    // 破棄予定のゲームオブジェクトを削除
    for (auto& gameObject : m_gameObjects)
    {
        if (gameObject->isMarkedForDestroy())
        {
            gameObject->Destroy();
        }
    }
}

//------------------
// ゲームオブジェクトを追加
//------------------
void Scene::addGameObject(std::unique_ptr<GameObject> gameObject)
{
    m_noStartObjects.push_back(gameObject.get());   // Startしていないゲームオブジェクトのリストに追加
    m_gameObjects.push_back(std::move(gameObject)); // ゲームオブジェクトのリストに追加
}
