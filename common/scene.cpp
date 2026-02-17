//--------------------------------------------
//
// シーン [scene.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "scene.h"

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
    if (m_activeScene != nullptr)
    {
        m_activeScene->update(elapsedTime, deltaTime); // アクティブシーンの更新
    }
}

//------------------
// シーンの描画
//------------------
void SceneManager::render(const Renderer& renderer)
{
    if (m_activeScene != nullptr)
    {
        m_activeScene->render(renderer); // アクティブシーンの描画
    }
}
