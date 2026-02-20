//--------------------------------------------
//
// 入力 [input.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "input.h"
#include <SDL3/SDL.h>
#include "log.h"
#include "gui.h"

//--------------------------------------
//
// 入力クラス
//
//--------------------------------------

//-------------------------
// 更新
//-------------------------
void Input::update()
{
    m_previousKeyState = m_currentKeyState; // 前回の状態を保存

    ImGuiIO& io = ImGui::GetIO(); // ImGuiのIOを取得

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

    for (SDL_Gamepad* gamepad : m_gamepads)
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
}

//-------------------------
// イベント処理
//-------------------------
bool Input::handleEvent(SDL_Event* event)
{
    // マウスホイール
    if (event->type == SDL_EVENT_MOUSE_WHEEL)
    {
        m_wheelX += event->wheel.x;
        m_wheelY += event->wheel.y;
    }

    // コントローラーの接続
    if (event->type == SDL_EVENT_GAMEPAD_ADDED)
    {
        // リストに追加
        SDL_Gamepad* gamepad = SDL_OpenGamepad(event->gdevice.which);
        if (gamepad != nullptr)
        {
            spdlog::info("コントローラー({})が接続されました。", SDL_GetGamepadName(gamepad));
            m_gamepads.push_back(gamepad);
        }
    }
    // コントローラーの切断
    if (event->type == SDL_EVENT_GAMEPAD_REMOVED)
    {
        // リストから削除する
        SDL_Gamepad* gamepad = SDL_GetGamepadFromID(event->gdevice.which);
        for (auto it = m_gamepads.begin(); it != m_gamepads.end(); ++it)
        {
            if (*it == gamepad)
            {
                m_gamepads.erase(it);
                break;
            }
        }
        SDL_CloseGamepad(gamepad); // デバイスを閉じる

        spdlog::info("コントローラーが切断されました。");
    }

    return true;
}

//-------------------------
// キーの状態を取得
//-------------------------
bool Input::isKeyPressed(int key) const
{
    if (!m_currentKeyState.contains(key) || !m_previousKeyState.contains(key)) return false;

    return m_currentKeyState.at(key) && !m_previousKeyState.at(key);
}
bool Input::isKeyReleased(int key) const
{
    if (!m_currentKeyState.contains(key) || !m_previousKeyState.contains(key)) return false;

    return !m_currentKeyState.at(key) && m_previousKeyState.at(key);
}
bool Input::isKeyDown(int key) const
{
    if (!m_currentKeyState.contains(key)) return false;

    return m_currentKeyState.at(key);
}
