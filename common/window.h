//--------------------------------------------
//
// ウインドウ [window.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once

class Renderer;
class Window;

namespace gui
{
    void init(const Window& window, const Renderer& renderer);
}

struct SDL_Window;
union SDL_Event;

// SDLのウィンドウのデリータ
struct SDLWindowDeleter
{
    void operator()(SDL_Window* window) const;
};

//-------------------------
// ウインドウクラス
//-------------------------
class Window
{
public:
    Window();
    ~Window();

    bool init(const char* title, int width, int height);
    void uninit();
    bool handleEvent(SDL_Event* event);

    void* getNativeWindow() const { return m_pNativeWindow; }

private:
    // ↓ friend Gui
    friend void gui::init(const Window& window, const Renderer& renderer);
    SDL_Window* getWindow() const;
    // ↑

    std::unique_ptr<SDL_Window, SDLWindowDeleter> m_pWindow; // SDLウインドウ
    void* m_pNativeWindow;                                   // 生のウィンドウ
};
