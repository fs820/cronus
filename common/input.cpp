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

namespace
{
    // キーコードとSDLのスキャンコードのマッピング
    const std::unordered_map<KeyCode, SDL_Scancode> keyCodeToScancode =
    {
        { KeyCode::A, SDL_SCANCODE_A },
        { KeyCode::B, SDL_SCANCODE_B },
        { KeyCode::C, SDL_SCANCODE_C },
        { KeyCode::D, SDL_SCANCODE_D },
        { KeyCode::E, SDL_SCANCODE_E },
        { KeyCode::F, SDL_SCANCODE_F },
        { KeyCode::G, SDL_SCANCODE_G },
        { KeyCode::H, SDL_SCANCODE_H },
        { KeyCode::I, SDL_SCANCODE_I },
        { KeyCode::J, SDL_SCANCODE_J },
        { KeyCode::K, SDL_SCANCODE_K },
        { KeyCode::L, SDL_SCANCODE_L },
        { KeyCode::M, SDL_SCANCODE_M },
        { KeyCode::N, SDL_SCANCODE_N },
        { KeyCode::O, SDL_SCANCODE_O },
        { KeyCode::P, SDL_SCANCODE_P },
        { KeyCode::Q, SDL_SCANCODE_Q },
        { KeyCode::R, SDL_SCANCODE_R },
        { KeyCode::S, SDL_SCANCODE_S },
        { KeyCode::T, SDL_SCANCODE_T },
        { KeyCode::U, SDL_SCANCODE_U },
        { KeyCode::V, SDL_SCANCODE_V },
        { KeyCode::W, SDL_SCANCODE_W },
        { KeyCode::X, SDL_SCANCODE_X },
        { KeyCode::Y, SDL_SCANCODE_Y },
        { KeyCode::Z, SDL_SCANCODE_Z },
        { KeyCode::Num0, SDL_SCANCODE_0 },
        { KeyCode::Num1, SDL_SCANCODE_1 },
        { KeyCode::Num2, SDL_SCANCODE_2 },
        { KeyCode::Num3, SDL_SCANCODE_3 },
        { KeyCode::Num4, SDL_SCANCODE_4 },
        { KeyCode::Num5, SDL_SCANCODE_5 },
        { KeyCode::Num6, SDL_SCANCODE_6 },
        { KeyCode::Num7, SDL_SCANCODE_7 },
        { KeyCode::Num8, SDL_SCANCODE_8 },
        { KeyCode::Num9, SDL_SCANCODE_9 },
        { KeyCode::Space, SDL_SCANCODE_SPACE },
        { KeyCode::Enter, SDL_SCANCODE_RETURN },
        { KeyCode::Escape, SDL_SCANCODE_ESCAPE },
        { KeyCode::LeftShift, SDL_SCANCODE_LSHIFT },
        { KeyCode::RightShift, SDL_SCANCODE_RSHIFT },
        { KeyCode::LeftCtrl, SDL_SCANCODE_LCTRL },
        { KeyCode::RightCtrl, SDL_SCANCODE_RCTRL },
        { KeyCode::LeftAlt, SDL_SCANCODE_LALT },
        { KeyCode::RightAlt, SDL_SCANCODE_RALT },
        { KeyCode::Tab, SDL_SCANCODE_TAB },
        { KeyCode::Backspace, SDL_SCANCODE_BACKSPACE },
        { KeyCode::CapsLock, SDL_SCANCODE_CAPSLOCK },
        { KeyCode::Left, SDL_SCANCODE_LEFT },
        { KeyCode::Right, SDL_SCANCODE_RIGHT },
        { KeyCode::Up, SDL_SCANCODE_UP },
        { KeyCode::Down, SDL_SCANCODE_DOWN },
        { KeyCode::F1, SDL_SCANCODE_F1 },
        { KeyCode::F2, SDL_SCANCODE_F2 },
        { KeyCode::F3, SDL_SCANCODE_F3 },
        { KeyCode::F4, SDL_SCANCODE_F4 },
        { KeyCode::F5, SDL_SCANCODE_F5 },
        { KeyCode::F6, SDL_SCANCODE_F6 },
        { KeyCode::F7, SDL_SCANCODE_F7 },
        { KeyCode::F8, SDL_SCANCODE_F8 },
        { KeyCode::F9, SDL_SCANCODE_F9 },
        { KeyCode::F10, SDL_SCANCODE_F10 },
        { KeyCode::F11, SDL_SCANCODE_F11 },
        { KeyCode::F12, SDL_SCANCODE_F12 },
        { KeyCode::Count, SDL_SCANCODE_UNKNOWN }
    };

    // マウスボタンコードとSDLのマウスボタンフラグのマッピング
    const std::unordered_map<MouseButtonCode, Uint32> mouseButtonCodeToFlag
    {
        { MouseButtonCode::Left, SDL_BUTTON_LEFT },
        { MouseButtonCode::Right, SDL_BUTTON_RIGHT },
        { MouseButtonCode::Middle, SDL_BUTTON_MIDDLE },
        { MouseButtonCode::Count, -1 }
    };

    // ゲームパッドボタンコードとSDLのゲームパッドボタンのマッピング
    const std::unordered_map<GamepadButtonCode, SDL_GamepadButton> gamepadButtonCodeToButton
    {
        { GamepadButtonCode::South, SDL_GAMEPAD_BUTTON_SOUTH },
        { GamepadButtonCode::East, SDL_GAMEPAD_BUTTON_EAST },
        { GamepadButtonCode::West, SDL_GAMEPAD_BUTTON_WEST },
        { GamepadButtonCode::North, SDL_GAMEPAD_BUTTON_NORTH },
        { GamepadButtonCode::LeftShoulder, SDL_GAMEPAD_BUTTON_LEFT_SHOULDER },
        { GamepadButtonCode::RightShoulder, SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER },
        { GamepadButtonCode::LeftTrigger, SDL_GAMEPAD_BUTTON_INVALID },
        { GamepadButtonCode::RightTrigger, SDL_GAMEPAD_BUTTON_INVALID },
        { GamepadButtonCode::Select, SDL_GAMEPAD_BUTTON_BACK },
        { GamepadButtonCode::Start, SDL_GAMEPAD_BUTTON_START },
        { GamepadButtonCode::LeftStick, SDL_GAMEPAD_BUTTON_LEFT_STICK },
        { GamepadButtonCode::RightStick, SDL_GAMEPAD_BUTTON_RIGHT_STICK },
        { GamepadButtonCode::Up, SDL_GAMEPAD_BUTTON_DPAD_UP },
        { GamepadButtonCode::Down, SDL_GAMEPAD_BUTTON_DPAD_DOWN },
        { GamepadButtonCode::Left, SDL_GAMEPAD_BUTTON_DPAD_LEFT },
        { GamepadButtonCode::Right, SDL_GAMEPAD_BUTTON_DPAD_RIGHT },
        { GamepadButtonCode::Count, SDL_GAMEPAD_BUTTON_INVALID }
    };
}

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
    ImGuiIO& io = ImGui::GetIO(); // ImGuiのIOを取得

    // キーボード
    m_keyboard.previousKeyState = m_keyboard.currentKeyState; // 前回の状態を保存
    if (!io.WantCaptureKeyboard)
    {
        // キーボードの状態を取得
        const bool* keyboardState = SDL_GetKeyboardState(nullptr);
        for (size_t count = 0; count < size_t(KeyCode::Count); ++count)
        {
            KeyCode key = KeyCode(count);
            if (keyboardState[keyCodeToScancode.at(key)])
            {
                m_keyboard.currentKeyState.try_emplace(key, false);
                m_keyboard.currentKeyState[key] = true;
            }
        }
    }

    // マウス
    m_mouse.relX = 0.0f; // 相対X座標をリセット
    m_mouse.relY = 0.0f; // 相対Y座標をリセット
    m_mouse.previousButtonState = m_mouse.currentButtonState; // 前回の状態を保存
    if (!io.WantCaptureMouse)
    {
        // マウスの位置と状態を取得
        Uint32 mouseState = SDL_GetMouseState(nullptr, nullptr);
        for (size_t count = 0; count < size_t(MouseButtonCode::Count); ++count)
        {
            MouseButtonCode button = MouseButtonCode(count);
            if (mouseState & SDL_BUTTON_MASK(mouseButtonCodeToFlag.at(button)))
            {
                m_mouse.currentButtonState.try_emplace(button, false);
                m_mouse.currentButtonState[button] = true;
            }
        }
    }

    for (Gamepad gamepad : m_gamepads)
    {
        // ボタン
        for (size_t count = 0; count < size_t(GamepadButtonCode::Count); ++count)
        {
            GamepadButtonCode button = GamepadButtonCode(count);
            if (gamepadButtonCodeToButton.at(button) == SDL_GAMEPAD_BUTTON_INVALID) continue;

            gamepad.currentButtonState.try_emplace(button, false);
            gamepad.currentButtonState[button] = SDL_GetGamepadButton(gamepad.device, gamepadButtonCodeToButton.at(button));
        }

        // スティック
        Sint16 rawX = SDL_GetGamepadAxis(gamepad.device, SDL_GAMEPAD_AXIS_LEFTX);
        Sint16 rawY = SDL_GetGamepadAxis(gamepad.device, SDL_GAMEPAD_AXIS_LEFTY);
        if (rawX < 0)
        {
            // 負の値は 32768.0f で割る
            gamepad.leftStickX = static_cast<float>(rawX) / 32768.0f;
        }
        else
        {
            // 正の値は 32767.0f で割る
            gamepad.leftStickX = static_cast<float>(rawX) / 32767.0f;
        }
        if (rawY < 0)
        {
            // 負の値は 32768.0f で割る
            gamepad.leftStickY = static_cast<float>(rawY) / 32768.0f;
        }
        else
        {
            // 正の値は 32767.0f で割る
            gamepad.leftStickY = static_cast<float>(rawY) / 32767.0f;
        }
        if (std::abs(gamepad.leftStickX) < m_deadZone) gamepad.leftStickX = 0.0f; // デッドゾーンを適用
        rawX = SDL_GetGamepadAxis(gamepad.device, SDL_GAMEPAD_AXIS_RIGHTX);
        rawY = SDL_GetGamepadAxis(gamepad.device, SDL_GAMEPAD_AXIS_RIGHTY);
        if (rawX < 0)
        {
            // 負の値は 32768.0f で割る
            gamepad.rightStickX = static_cast<float>(rawX) / 32768.0f;
        }
        else
        {
            // 正の値は 32767.0f で割る
            gamepad.rightStickX = static_cast<float>(rawX) / 32767.0f;
        }
        if (rawY < 0)
        {
            // 負の値は 32768.0f で割る
            gamepad.rightStickY = static_cast<float>(rawY) / 32768.0f;
        }
        else
        {
            // 正の値は 32767.0f で割る
            gamepad.rightStickY = static_cast<float>(rawY) / 32767.0f;
        }
        if (std::abs(gamepad.rightStickX) < m_deadZone) gamepad.rightStickX = 0.0f; // デッドゾーンを適用

        // トリガー
        rawX = SDL_GetGamepadAxis(gamepad.device, SDL_GAMEPAD_AXIS_LEFT_TRIGGER);
        if (rawX < 0)
        {
            // 負の値は 32768.0f で割る
            gamepad.leftTrigger = static_cast<float>(rawX) / 32768.0f;
        }
        else
        {
            // 正の値は 32767.0f で割る
            gamepad.leftTrigger = static_cast<float>(rawX) / 32767.0f;
        }
        rawX = SDL_GetGamepadAxis(gamepad.device, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER);
        if (rawX < 0)
        {
            // 負の値は 32768.0f で割る
            gamepad.rightTrigger = static_cast<float>(rawX) / 32768.0f;
        }
        else
        {
            // 正の値は 32767.0f で割る
            gamepad.rightTrigger = static_cast<float>(rawX) / 32767.0f;
        }

        // トリガーの状態を更新
        if (gamepad.leftTrigger >= m_triggerThreshold)
        {
            gamepad.currentButtonState.try_emplace(GamepadButtonCode::LeftTrigger, false);
            gamepad.currentButtonState[GamepadButtonCode::LeftTrigger] = true;
        }
        if (gamepad.rightTrigger >= m_triggerThreshold)
        {
            gamepad.currentButtonState.try_emplace(GamepadButtonCode::RightTrigger, false);
            gamepad.currentButtonState[GamepadButtonCode::RightTrigger] = true;
        }
    }
}

//-------------------------
// イベント処理
//-------------------------
bool Input::handleEvent(SDL_Event* event)
{
    // マウス移動
    if (event->type == SDL_EVENT_MOUSE_MOTION)
    {
        // 絶対座標を更新 (UIなどで使う用)
        m_mouse.x = event->motion.x;
        m_mouse.y = event->motion.y;

        // 移動量を蓄積 (カメラ操作などで使う用)
        m_mouse.relX += event->motion.xrel;
        m_mouse.relY += event->motion.yrel;
    }

    // マウスホイール
    if (event->type == SDL_EVENT_MOUSE_WHEEL)
    {
        m_mouse.wheelX += event->wheel.x;
        m_mouse.wheelY += event->wheel.y;
    }

    // コントローラーの接続
    if (event->type == SDL_EVENT_GAMEPAD_ADDED)
    {
        // リストに追加
        SDL_Gamepad* gamepad = SDL_OpenGamepad(event->gdevice.which);
        if (gamepad != nullptr)
        {
            spdlog::info("コントローラー({})が接続されました。", SDL_GetGamepadName(gamepad));
            m_gamepads.emplace_back(Gamepad(gamepad));
        }
    }
    // コントローラーの切断
    if (event->type == SDL_EVENT_GAMEPAD_REMOVED)
    {
        // リストから削除する
        SDL_Gamepad* gamepad = SDL_GetGamepadFromID(event->gdevice.which);
        for (auto it = m_gamepads.begin(); it != m_gamepads.end(); ++it)
        {
            if (it->device == gamepad)
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
bool Input::isKeyPressed(KeyCode key) const
{
    if (!m_keyboard.currentKeyState.contains(key) || !m_keyboard.previousKeyState.contains(key)) return false;

    return m_keyboard.currentKeyState.at(key) && !m_keyboard.previousKeyState.at(key);
}
bool Input::isKeyReleased(KeyCode key) const
{
    if (!m_keyboard.currentKeyState.contains(key) || !m_keyboard.previousKeyState.contains(key)) return false;

    return !m_keyboard.currentKeyState.at(key) && m_keyboard.previousKeyState.at(key);
}
bool Input::isKeyDown(KeyCode key) const
{
    if (!m_keyboard.currentKeyState.contains(key)) return false;

    return m_keyboard.currentKeyState.at(key);
}
bool Input::isMouseButtonPressed(MouseButtonCode button) const
{
    if (!m_mouse.currentButtonState.contains(button) || !m_mouse.previousButtonState.contains(button)) return false;

    return m_mouse.currentButtonState.at(button) && !m_mouse.previousButtonState.at(button);
}
bool Input::isMouseButtonReleased(MouseButtonCode button) const
{
    if (!m_mouse.currentButtonState.contains(button) || !m_mouse.previousButtonState.contains(button)) return false;

    return !m_mouse.currentButtonState.at(button) && m_mouse.previousButtonState.at(button);
}
bool Input::isMouseButtonDown(MouseButtonCode button) const
{
    if (!m_mouse.currentButtonState.contains(button)) return false;

    return m_mouse.currentButtonState.at(button);
}
bool Input::isGamepadButtonPressed(GamepadButtonCode button, size_t id) const
{
    if (m_gamepads.empty()) return false;
    if (id >= m_gamepads.size()) return false;

    const Gamepad& gamepad = m_gamepads[id];
    if (!gamepad.currentButtonState.contains(button) || !gamepad.previousButtonState.contains(button)) return false;

    return gamepad.currentButtonState.at(button) && !gamepad.previousButtonState.at(button);

}
bool Input::isGamepadButtonReleased(GamepadButtonCode button, size_t id) const
{
    if (m_gamepads.empty()) return false;
    if (id >= m_gamepads.size()) return false;

    const Gamepad& gamepad = m_gamepads[id];
    if (!gamepad.currentButtonState.contains(button) || !gamepad.previousButtonState.contains(button)) return false;

    return !gamepad.currentButtonState.at(button) && gamepad.previousButtonState.at(button);
}
bool Input::isGamepadButtonDown(GamepadButtonCode button, size_t id) const
{
    if (m_gamepads.empty()) return false;
    if (id >= m_gamepads.size()) return false;

    const Gamepad& gamepad = m_gamepads[id];
    if (!gamepad.currentButtonState.contains(button)) return false;

    return gamepad.currentButtonState.at(button);
}
bool Input::isActionPressed(ActionCode action) const
{
    return false;
}
bool Input::isActionReleased(ActionCode action) const
{
    return false;
}
bool Input::isActionDown(ActionCode action) const
{
    return false;
}
