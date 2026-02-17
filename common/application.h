//--------------------------------------------
//
// アプリケーション [application.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#include <memory>
union SDL_Event;

class Window;
class Renderer;
class TextureManager;
class MeshManager;
class ModelManager;
class PhysicsManager;
class SoundManager;
class EventDispatcher;
class Camera;

constexpr const char* DEFAULT_WINDOW_TITLE = "アプリケーション";
constexpr int DEFAULT_WINDOW_WIDTH = 1920;
constexpr int DEFAULT_WINDOW_HEIGHT = 1080;

//---------------------------------------------------------------------
// アプリケーションクラス
// SDLのエントリーポイントにより生成され各MainSystemを持つ基底クラス
// これを継承し各ゲームのmainのクラスを作成する
//---------------------------------------------------------------------
class Application
{
public:
    Application();
    ~Application();

    bool init(int argc, char* argv[]);
    void uninit();
    bool update();
    bool render();
    bool handleEvent(SDL_Event* event);

    Window* getWindow();
    Renderer* getRenderer();
    TextureManager* getTextureManager();
    MeshManager* getMeshManager();
    ModelManager* getModelManager();
    PhysicsManager* getPhysicsManager();
    SoundManager* getSoundManager();
    EventDispatcher* getEventDispatcher();
    Camera* getCamera();

protected:
    virtual bool onStart() = 0;
    virtual void onEnd() = 0;
    virtual bool onUpdate(float elapsedTime, float deltaTime) = 0;
    virtual bool onRender(const Renderer& renderer) = 0;
    virtual bool onEvent(SDL_Event* event) = 0;

private:
    std::unique_ptr<Window> m_pWindow;
    std::unique_ptr<Renderer> m_pRenderer;
    std::unique_ptr<TextureManager> m_pTextureManager;
    std::unique_ptr<MeshManager> m_pMeshManager;
    std::unique_ptr<ModelManager> m_pModelManager;
    std::unique_ptr<PhysicsManager> m_pPhysicsManager;
    std::unique_ptr<SoundManager> m_pSoundManager;
    std::unique_ptr<EventDispatcher> m_pEventDispatcher;
    std::unique_ptr<Camera> m_pCamera;

    uint64_t m_frequency;
    uint64_t m_startCounter;
    uint64_t m_lastCounter;
    bool m_isGuiSetup;
};
