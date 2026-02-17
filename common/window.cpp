//--------------------------------------------
//
// ウインドウ [window.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "window.h"
#include <SDL3/SDL.h>
#include "gui.h"

// デリータでSDL_DestroyWindowを呼ぶ
void SDLWindowDeleter::operator()(SDL_Window* window) const
{
    SDL_DestroyWindow(window);
}

//------------------------------------------
// 
// ウィンドウクラス
// 
//------------------------------------------
Window::Window() : m_pWindow{}, m_pNativeWindow{} {}
Window::~Window() { uninit(); }   // SDL_Quit漏れを防ぐ

//------------------------------------------
// 初期化
//------------------------------------------
bool Window::init(const char* title, int width, int height)
{
    // SDLの初期化
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
    {
        std::cout << "SDLの初期化に失敗しました:" << SDL_GetError() << std::endl;
        return false;
    }

    // ウィンドウの作成
    m_pWindow.reset(SDL_CreateWindow(
        title,  // タイトル
        width,  // 幅
        height, // 高さ
        0       // WindowType
    ));
    if (m_pWindow == nullptr)
    {
        std::cout << "ウィンドウの作成に失敗しました:" << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    // ネイティブウィンドウハンドル取得
    m_pNativeWindow = SDL_GetPointerProperty(
        SDL_GetWindowProperties(m_pWindow.get()), // ウィンドウのプロパティを取得
        SDL_PROP_WINDOW_WIN32_HWND_POINTER,       // WindowsのHWND指定
        nullptr                                   // デフォルト値はnull
    );
    if (m_pNativeWindow == nullptr)
    {
        std::cout << "HWNDの取得に失敗しました:" << SDL_GetError() << std::endl;
    }

    return true;
}

//------------------------------------------
// 破棄
//------------------------------------------
void Window::uninit()
{
    m_pWindow.reset(); // ウィンドウをリセット
    SDL_Quit();        // SDLの終了
}

//------------------------------------------
// 更新
//------------------------------------------
bool Window::handleEvent(SDL_Event* event)
{
    // ウィンドウの[X]ボタンが押された時の処理
    if (event->type == SDL_EVENT_QUIT)
    {
        const SDL_MessageBoxButtonData buttons[] =
        {
            { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "キャンセル" }, // ID 0
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "終了する" },   // ID 1
        };
        const SDL_MessageBoxData messageboxdata =
        {
            SDL_MESSAGEBOX_INFORMATION,
            m_pWindow.get(), // 親ウィンドウ
            "終了確認",
            "アプリケーションを終了しますか？",
            SDL_arraysize(buttons),
            buttons,
            NULL
        };

        int buttonid = -1;
        SDL_ShowMessageBox(&messageboxdata, &buttonid);

        if (buttonid == 1)
        { // 終了する(ID 1) が押された
            return false;
        }
    }

    // キーが押された時の処理
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        switch (event->key.key)
        {
        case SDLK_F11:
        {// フルスクリーン切り替え
            // 現在のウィンドウフラグを取得
            SDL_WindowFlags flags = SDL_GetWindowFlags(m_pWindow.get());

            if (flags & SDL_WINDOW_FULLSCREEN)
            {
                // ウィンドウモードに戻す
                SDL_SetWindowFullscreen(m_pWindow.get(), false);
            }
            else
            {
                // フルスクリーンにする
                SDL_SetWindowFullscreen(m_pWindow.get(), true);
            }
            break;
        }
        case SDLK_ESCAPE:
        {// 終了確認
            const SDL_MessageBoxButtonData buttons[] =
            {
                { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "キャンセル" }, // ID 0
                { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "終了する" },   // ID 1
            };
            const SDL_MessageBoxData messageboxdata =
            {
                SDL_MESSAGEBOX_INFORMATION,
                m_pWindow.get(), // 親ウィンドウ
                "終了確認",
                "アプリケーションを終了しますか？",
                SDL_arraysize(buttons),
                buttons,
                NULL
            };

            int buttonid = -1; // 押されたボタンのIDが入る
            SDL_ShowMessageBox(&messageboxdata, &buttonid);

            if (buttonid == 1)
            { // 終了する(ID 1) が押された
                return false;
            }
            break;
        }
        }
    }

    //------------------------
    // 入力イベント関連
    //------------------------
    ImGuiIO& io = ImGui::GetIO();

    // キーボード
    if (!io.WantCaptureKeyboard)
    {
        // キーボードの状態を取得
        const bool* keyboardState = SDL_GetKeyboardState(nullptr);
        if (keyboardState[SDL_SCANCODE_W])
        {
            std::cout << "W is Down:" << std::endl;
        }
    }

    // マウス
    if (!io.WantCaptureMouse)
    {
        // マウスの位置と状態を取得
        float mouseX, mouseY;
        Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

        std::cout << "Mouse:" << mouseX << "," << mouseY << std::endl;

        if (mouseState & SDL_BUTTON_LMASK)
        {
            std::cout << "Mouse Left is Down:" << std::endl;
        }
    }

    // コントローラーの接続
    std::vector<SDL_Gamepad*> gamepads;
    if (event->type == SDL_EVENT_GAMEPAD_ADDED)
    {
        int deviceIndex = event->gdevice.which;
        SDL_Gamepad* gamepad = SDL_OpenGamepad(deviceIndex);
        if (gamepad)
        {
            std::cout << SDL_GetGamepadName(gamepad) << "が接続されました。" << std::endl;
            gamepads.push_back(gamepad); // リストに追加
        }
    }
    // コントローラーの切断
    if (event->type == SDL_EVENT_GAMEPAD_REMOVED)
    {
        SDL_Gamepad* gamepad = SDL_GetGamepadFromID(event->gdevice.which);
        // リストから削除する
        for (auto it = gamepads.begin(); it != gamepads.end(); ++it) {
            if (*it == gamepad) {
                gamepads.erase(it);
                break;
            }
        }
        SDL_CloseGamepad(gamepad); // デバイスを閉じる
        std::cout << "コントローラーが切断されました。" << std::endl;
    }

    for (SDL_Gamepad* gamepad : gamepads)
    {
        // ボタン
        if (SDL_GetGamepadButton(gamepad, SDL_GAMEPAD_BUTTON_SOUTH)) // 下のボタン
        {
            std::cout << "South" << std::endl;
        }

        // スティック
        Sint16 rawX = SDL_GetGamepadAxis(gamepad, SDL_GAMEPAD_AXIS_LEFTX);
        Sint16 rawY = SDL_GetGamepadAxis(gamepad, SDL_GAMEPAD_AXIS_LEFTY);
        float leftX{}, leftY{};
        if (rawX < 0)
        {
            // 負の値は 32768.0f で割る
            leftX = static_cast<float>(rawX) / 32768.0f;
        }
        else
        {
            // 正の値は 32767.0f で割る
            leftX = static_cast<float>(rawX) / 32767.0f;
        }
        if (rawY < 0)
        {
            // 負の値は 32768.0f で割る
            leftY = static_cast<float>(rawY) / 32768.0f;
        }
        else
        {
            // 正の値は 32767.0f で割る
            leftY = static_cast<float>(rawY) / 32767.0f;
        }

        float length = hypotf(leftX, leftY);
        if (length < 0.1f)
        {
            leftX = 0.0f; leftY = 0.0f;
        }
    }

    return true;
}

//------------------------
// タイトルの設定
//------------------------
void Window::setTitle(const char* title)
{
    SDL_SetWindowTitle(m_pWindow.get(), title);
}

//------------------------------------------
// ウィンドウの取得 (限定的)
//------------------------------------------
SDL_Window* Window::getWindow() const { return m_pWindow.get(); }
