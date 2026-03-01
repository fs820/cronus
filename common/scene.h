//--------------------------------------------
//
// シーン [scene.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include <span>
#include "object.h"

class Scene;
class Renderer;
class Camera;

//---------------------------------------------
// シーン管理クラス
//---------------------------------------------
class SceneManager
{
public:
    SceneManager() = default;
    ~SceneManager() = default;

    void addScene(std::string_view sceneName, Scene* scene);
    void changeScene(std::string_view sceneName);
    void update(float elapsedTime, float deltaTime);

    Scene* getActiveScene() const { return m_activeScene; }

private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> m_scenes;
    Scene* m_activeScene = nullptr;
};

//---------------------------------------------
// シーンクラス
//---------------------------------------------
class Scene
{
public:
    Scene();
    virtual ~Scene();

    virtual void onEnter() {}                                  // シーンに入るときの処理
    virtual void onExit() {}                                   // シーンから出るときの処理

    void update(float elapsedTime, float deltaTime); // 更新処理
    void addGameObject(std::unique_ptr<GameObject> gameObject);

    //-------------------------------------------------------------------
    // ゲームオブジェクトのうち、指定したコンポーネントを持つものを取得
    //-------------------------------------------------------------------
    template<typename T>
    std::span<T*> getGameObjectsOfType() const
    {
        std::vector<T*> result;
        for (const auto& gameObject : m_gameObjects)
        {
            if (gameObject->Has<T>())
            {
                result.push_back(&gameObject->Get<T>());
            }
        }
        return result;
    }

protected:
    virtual void onUpdate(float, float) {}

private:
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;  // ゲームオブジェクトのリスト
    std::vector<GameObject*> m_noStartObjects;               // Startしていないゲームオブジェクトのリスト
};
