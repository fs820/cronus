#pragma once

#include "imgui.h" // ImGui名前空間の呼び出しを公開

class Renderer;

namespace gui
{
    void init(const Renderer& renderer);
    void uninit();
    void beginFrame();
    void endFrame();
    void draw();
}
