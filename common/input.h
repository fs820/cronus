//--------------------------------------------
//
// 入力 [input.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#include <unordered_map>

union SDL_Event;
struct SDL_Gamepad;

//--------------------------------------
//
// 入力クラス
//
//--------------------------------------
class Input
{
public:
    Input() = default;
    ~Input() = default;

    void update();
    bool handleEvent(SDL_Event* event);

    bool isKeyPressed(int key) const;
    bool isKeyReleased(int key) const;
    bool isKeyDown(int key) const;

private:
    std::vector<SDL_Gamepad*> m_gamepads;

    std::unordered_map<int, bool> m_currentKeyState; // 現在のキー状態
    std::unordered_map<int, bool> m_previousKeyState; // 前回のキー状態

    float m_wheelX; // マウスホイールの水平スクロール量
    float m_wheelY; // マウスホイールの垂直スクロール量
};
