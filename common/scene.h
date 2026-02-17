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

class Scene;
class Renderer;

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
    void render(const Renderer& renderer);

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
    Scene() = default;
    virtual ~Scene() = default;

    virtual void onEnter() {}                                  // シーンに入るときの処理
    virtual void onExit() {}                                   // シーンから出るときの処理
    virtual void update(float elapsedTime, float deltaTime) {} // 更新処理
    virtual void render(const Renderer& renderer) {}           // 描画処理

private:
};
