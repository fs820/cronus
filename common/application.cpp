//--------------------------------------------
//
// アプリケーション [application.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "application.h"
#include <SDL3/SDL.h>
#include <imgui_impl_sdl3.h>
#include "window.h"
#include "renderer.h"
#include "gui.h"
#include "texture.h"
#include "mesh.h"
#include "model.h"
#include "physics.h"
#include "sound.h"
#include "event.h"
#include "camera.h"

//------------------------------------------
// 
// アプリケーションクラス
// 
//------------------------------------------
Application::Application() : m_pWindow{}, m_pRenderer{}, m_pTextureManager{}, m_pMeshManager{}, m_pModelManager{}, m_pPhysicsManager{}, m_pSoundManager{}, m_pEventDispatcher{}, m_pCamera{}, m_frequency{}, m_startCounter{}, m_lastCounter{}, m_isGuiSetup{} {}
Application::~Application() = default;

//------------------------------------------
// 初期化
//------------------------------------------
bool Application::init(int argc, char* argv[])
{
    // 固定の初期化

    // ウインドウ
    m_pWindow = std::make_unique<Window>();
    if (!m_pWindow->init(DEFAULT_WINDOW_TITLE, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT)) return false;

    // レンダラー
    m_pRenderer = std::make_unique<Renderer>();
    m_pRenderer->init(static_cast<HWND>(m_pWindow->getNativeWindow()), DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);

    // 物理
    m_pPhysicsManager = std::make_unique<PhysicsManager>();
    m_pPhysicsManager->init();

    m_pTextureManager = std::make_unique<TextureManager>();             // テクスチャ
    m_pMeshManager = std::make_unique<MeshManager>(*m_pRenderer.get()); // メッシュ
    m_pModelManager = std::make_unique<ModelManager>();                 // モデル
    m_pSoundManager = std::make_unique<SoundManager>();                 // サウンド
    m_pEventDispatcher = std::make_unique<EventDispatcher>();           // イベント
    m_pCamera = std::make_unique<Camera>();                             // カメラ

    // Gui
    gui::init(*m_pWindow.get(), *m_pRenderer.get());
    m_isGuiSetup = true;

    m_frequency = SDL_GetPerformanceFrequency();  // 1秒あたりのカウント
    m_startCounter = SDL_GetPerformanceCounter(); // 始まりのカウント
    m_lastCounter = m_startCounter;               // 前回のカウント

    // ゲームの開始
    return onStart();
}

//------------------------------------------
// 破棄
//------------------------------------------
void Application::uninit()
{
    // ゲームの終了
    onEnd();

    // 固定の破棄
    gui::uninit();
    m_pPhysicsManager->uninit();
    m_pRenderer->uninit();
    m_pWindow->uninit();
}

//------------------------------------------
// 更新
//------------------------------------------
bool Application::update()
{
    gui::beginFrame(); // Gui開始

    // 固定の更新

    // 現在のカウント
    Uint64 currentCounter = SDL_GetPerformanceCounter();

    // 現在のカウント / 1秒あたりのカウント数 = 経過秒数
    float elapsedTime = static_cast<float>(currentCounter - m_startCounter) / static_cast<float>(m_frequency);

    // カウント差分 / 1秒あたりのカウント数 = 経過秒数
    float deltaTime = static_cast<float>(currentCounter - m_lastCounter) / static_cast<float>(m_frequency);

    // 保存
    m_lastCounter = currentCounter;
    
    // ゲームの更新
    if (!onUpdate(elapsedTime, deltaTime)) return false;

    // 物理シミュレーション
    m_pPhysicsManager->simulate(deltaTime);

    gui::endFrame(); // Gui終了
    return true;
}

//------------------------------------------
// 描画
//------------------------------------------
bool Application::render()
{
    m_pRenderer->beginUI(true); // 描画開始

    gui::draw();     // Gui描画

    m_pRenderer->endUI(); // 描画終了

    m_pRenderer->present(); // 表示
    return true;
}

//------------------------------------------
// イベント
//------------------------------------------
bool Application::handleEvent(SDL_Event* event)
{
    // 固定のイベント
    if (m_isGuiSetup) ImGui_ImplSDL3_ProcessEvent(event); // Gui
    if (!m_pWindow->handleEvent(event)) return false;     // ウインドウ

    // ゲームのイベント
    return onEvent(event);
}

//------------------------------------------
// ゲッター
//------------------------------------------
Window* Application::getWindow() { return m_pWindow.get(); }
Renderer* Application::getRenderer() { return m_pRenderer.get(); }
TextureManager* Application::getTextureManager() { return m_pTextureManager.get(); }
MeshManager* Application::getMeshManager() { return m_pMeshManager.get(); }
ModelManager* Application::getModelManager() { return m_pModelManager.get(); }
PhysicsManager* Application::getPhysicsManager() { return m_pPhysicsManager.get(); }
SoundManager* Application::getSoundManager() { return m_pSoundManager.get(); }
EventDispatcher* Application::getEventDispatcher() { return m_pEventDispatcher.get(); }
Camera* Application::getCamera() { return m_pCamera.get(); }
