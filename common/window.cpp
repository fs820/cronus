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

// デリータでSDL_DestroyWindowを呼ぶ
void SDLCursorDeleter::operator()(SDL_Cursor* cursor) const
{
    SDL_DestroyCursor(cursor);
}

//------------------------------------------
// 
// ウィンドウクラス
// 
//------------------------------------------
Window::Window() : m_pWindow{}, m_pNativeWindow{}, m_pCursor{}, m_inputText{}, m_editingText{}, m_isInputComplete{} {}
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
    m_pCursor.reset(); // カーソルをリセット
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
                setFullscreen(false);
            }
            else
            {
                // フルスクリーンにする
                setFullscreen(true);
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

    // テキスト入力の処理
    switch (event->type)
    {
        // 文字が確定入力された時（半角英数、またはIMEで変換確定した時）
    case SDL_EVENT_TEXT_INPUT:
        m_inputText += event->text.text;
        break;
        // IMEで日本語を変換中の時（未確定の文字列）
    case SDL_EVENT_TEXT_EDITING:
        m_editingText = event->edit.text; // 変換中の文字を保持
        break;
        // BackspaceやEnterなどの制御キーの処理
    case SDL_EVENT_KEY_DOWN:
        if (event->key.key == SDLK_BACKSPACE && m_inputText.length() > 0)
        {
            // マルチバイト文字を考慮して消す
            PopBackUtf8(m_inputText);
        }
        else if (event->key.key == SDLK_RETURN)
        {
            // Enterキーで入力完了
            if (m_editingText.empty())
            { // 変換中でなければ決定
                m_isInputComplete = true;
                SDL_StopTextInput(m_pWindow.get()); // 入力モード終了
            }
        }
        break;
    }

    return true;
}

//------------------------
// アイコンの設定
//------------------------
void Window::setIcon(const std::filesystem::path& iconPath)
{
    // 画像を読み込む
    SDL_Surface* iconSurface = SDL_LoadBMP(iconPath.string().c_str());
    if (iconSurface != nullptr)
    {
        // ウィンドウに設定
        SDL_SetWindowIcon(m_pWindow.get(), iconSurface);

        // データ解放
        SDL_DestroySurface(iconSurface);
    }
    else
    {
        SDL_Log("アイコンの読み込みに失敗: %s", SDL_GetError());
    }
}

//------------------------
// カーソルの設定
//------------------------
void Window::setCursor(const std::filesystem::path& cursorPath, int hotspotX, int hotspotY)
{
    // 画像読み込み
    SDL_Surface* cursorSurface = SDL_LoadBMP(cursorPath.string().c_str());
    if (cursorSurface != nullptr)
    {
        // カーソルを作成
        SDL_Cursor* cursor = SDL_CreateColorCursor(cursorSurface, hotspotX, hotspotY);
        if (cursor != nullptr)
        {
            // アクティブなカーソルとして設定
            SDL_SetCursor(cursor);

            // 保持
            m_pCursor.reset(cursor);
        }

        // データ解放
        SDL_DestroySurface(cursorSurface);
    }
}

//------------------------
// タイトルの設定
//------------------------
void Window::setTitle(const char* title)
{
    SDL_SetWindowTitle(m_pWindow.get(), title);
}

//------------------------------------------
// ウィンドウのサイズ設定
//------------------------------------------
void Window::setSize(int width, int height)
{
    SDL_SetWindowSize(m_pWindow.get(), width, height);
}

//------------------------------------------
// フルスクリーンの切り替え
//------------------------------------------
void Window::setFullscreen(bool fullscreen)
{
    SDL_SetWindowFullscreen(m_pWindow.get(), fullscreen);
}

//------------------------------------------
// カーソルの表示切り替え
//------------------------------------------
void Window::setCursorVisible(bool visible)
{
    if (visible)
    {
        SDL_ShowCursor();
    }
    else
    {
        SDL_HideCursor();
    }
}

//------------------------------------------
// 入力テキストの開始
//------------------------------------------
void Window::startInputText(int posX, int posY, int scaleX, int scaleY)
{
    m_inputText.clear();       // 入力済み文字列をクリア
    m_editingText.clear();     // 変換中文字列をクリア
    m_isInputComplete = false; // 入力完了フラグをリセット

    // 入力モードを開始する（IMEが有効になる）
    SDL_StartTextInput(m_pWindow.get());

    // IMEの変換候補ウィンドウ（予測変換のリスト）が出る位置をOSに教える
    SDL_Rect rect = { posX, posY, scaleX, scaleY }; // 入力欄の画面上の座標とサイズ
    SDL_SetTextInputArea(m_pWindow.get(), &rect, 0);
}

//------------------------------------------
// ウィンドウの取得 (限定的)
//------------------------------------------
SDL_Window* Window::getWindow() const { return m_pWindow.get(); }
