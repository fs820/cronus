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
    bool handleEvent(SDL_Event* event);

    Window* getWindow();

protected:
    virtual bool onStart() = 0;
    virtual void onEnd() = 0;
    virtual bool onUpdate(float elapsedTime, float deltaTime) = 0;
    virtual bool onEvent(SDL_Event* event) = 0;

private:
    std::unique_ptr<Window> m_pWindow;

    uint64_t m_frequency;
    uint64_t m_startCounter;
    uint64_t m_lastCounter;
};
