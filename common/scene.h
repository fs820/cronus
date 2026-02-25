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
class GameObject;
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

    Camera* getCamera() const { return m_camera.get(); }

protected:
    virtual void onUpdate(float, float) {}

private:
    std::unique_ptr<Camera> m_camera;                        // カメラ
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;  // ゲームオブジェクトのリスト
    std::vector<GameObject*> m_noStartObjects;               // Startしていないゲームオブジェクトのリスト
};
