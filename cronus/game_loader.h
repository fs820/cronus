//--------------------------------------------
//
// Gameローダー [game_loader.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#include <filesystem>

struct Config
{
    int windowWidth;  // ウィンドウ幅
    int windowHeight; // ウィンドウ高さ
};

namespace file
{
    // 読み込み
    Config loadConfig(const std::filesystem::path& path);
}
