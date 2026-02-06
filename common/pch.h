#pragma once

// C
#define NOMINMAX
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <strsafe.h>

// C++(std)
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <filesystem>
#include <span>
#include <unordered_map>
#include <fstream>
#include <chrono>
#include <thread>
#include <future>
#include <atomic>

#define STR(var) #var

inline std::wstring Utf8ToWide(const std::string& text) {
    if (text.empty()) return L"";

    // 必要なバッファサイズを計算
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &text[0], (int)text.size(), NULL, 0);

    std::wstring wstrTo(size_needed, 0);

    // 変換実行
    MultiByteToWideChar(CP_UTF8, 0, &text[0], (int)text.size(), &wstrTo[0], size_needed);

    return wstrTo;
}

inline std::u8string toU8String(const std::string& s)
{
    return std::u8string(s.begin(), s.end());
}

inline std::string ToUtf8String(std::u8string_view s)
{
    return std::string(s.begin(), s.end());
}

inline std::string ToUtf8String(const std::filesystem::path& p)
{
    auto u8 = p.u8string();
    return std::string(u8.begin(), u8.end());
}

constexpr uint64_t Hash(const char* str)
{
    uint64_t h = 2166136261u; // FNV-1a
    while (*str)
    {
        h ^= static_cast<uint8_t>(*str++);
        h *= 16777619u;
    }
    return h;
}

constexpr uint64_t Hash(const char8_t* str)
{
    uint64_t h = 2166136261u; // FNV-1a
    while (*str)
    {
        h ^= static_cast<uint8_t>(*str++);
        h *= 16777619u;
    }
    return h;
}
