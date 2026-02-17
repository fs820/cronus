//--------------------------------------------
//
// テキストローダー [text_loader.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#include "text_loader.h"

namespace file
{
    //---------------
    // 読み込み
    //---------------
    std::string loadText(const std::filesystem::path& path)
    {
        NativeFile file(path, FileMode::ReadText);
        return file.read();
    }

    //----------------
    // 書き込み
    //----------------
    bool saveText(const std::filesystem::path& path, std::string_view content)
    {
        NativeFile file(path, FileMode::WriteText);
        file.write(content);
        return true;
    }
}
