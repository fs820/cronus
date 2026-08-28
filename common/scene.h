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
#include <typeindex>
#include <vector>
#include "object.h"
#include "component_registry.h"

class Scene;
class Renderer;
class Camera;
class Application;

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
    void lateUpdate(float elapsedTime, float deltaTime);
    void cleanup();

    Scene* getActiveScene() const { return m_activeScene; }

private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> m_scenes;
    Scene* m_activeScene = nullptr;
};

//---------------------------------------------
// シーンクラス (IComponentRegistryを継承)
//---------------------------------------------
class Scene : public IComponentRegistry
{
public:
    Scene(Application* pApp);
    virtual ~Scene();

    virtual void onEnter() {}                                  // シーンに入るときの処理
    virtual void onExit() {}                                   // シーンから出るときの処理

    void update(float elapsedTime, float deltaTime);     // 更新処理
    void lateUpdate(float elapsedTime, float deltaTime); // 更新処理
    void cleanup();

    void addGameObject(std::unique_ptr<GameObject> gameObject);

    void registerComponent(Component* comp) override;
    void unregisterComponent(Component* comp) override;

    //-------------------------------------------------------------------
    // ゲームオブジェクトのうち、指定したコンポーネントを持つものを取得
    //-------------------------------------------------------------------
    template<typename T>
    std::vector<T*> getComponentsOfType() const
    {
        std::vector<T*> result;

        // キャッシュされているすべてのコンポーネントリストを走査する
        for (const auto& pair : m_componentCaches)
        {
            for (auto* comp : pair.second)
            {
                // dynamic_castT型に変換できるか
                if (auto casted = dynamic_cast<T*>(comp))
                {
                    result.push_back(casted);
                }
            }
        }
        return result;
    }

protected:
    virtual void onUpdate(float, float) {}
    Application* getApp() { return m_pApp; }

private:
    Application* m_pApp;

    // 型情報をキーにして、そのコンポーネントのポインタ配列を保持するマップ
    std::unordered_map<std::type_index, std::vector<Component*>> m_componentCaches;

    std::vector<std::unique_ptr<GameObject>> m_gameObjects;  // ゲームオブジェクトのリスト
    std::vector<GameObject*> m_noStartObjects;               // Startしていないゲームオブジェクトのリスト
};
