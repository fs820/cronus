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

//------------------------------------------
// 
// アプリケーションクラス
// 
//------------------------------------------
Application::Application() : m_pWindow{}, m_frequency{}, m_startCounter{}, m_lastCounter{} {}
Application::~Application() = default;

//------------------------------------------
// 初期化
//------------------------------------------
bool Application::init(int argc, char* argv[])
{
    // 固定の初期化
    m_pWindow = std::make_unique<Window>();
    if (!m_pWindow->init(DEFAULT_WINDOW_TITLE, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT)) return false;

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
    m_pWindow->uninit();
}

//------------------------------------------
// 更新
//------------------------------------------
bool Application::update()
{
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
    return onUpdate(elapsedTime, deltaTime);
}

//------------------------------------------
// イベント
//------------------------------------------
bool Application::handleEvent(SDL_Event* event)
{
    // 固定のイベント
    ImGui_ImplSDL3_ProcessEvent(event);               // Gui
    if (!m_pWindow->handleEvent(event)) return false; // ウインドウ

    // ゲームのイベント
    return onEvent(event);
}

Window* Application::getWindow() { return m_pWindow.get(); }
