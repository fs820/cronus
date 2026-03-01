//--------------------------------------------
//
// タイトルロゴ[title_rogo.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#include <memory>

class GameObject;
class MeshManager;
struct TextureHandle;

namespace factory
{
    std::unique_ptr<GameObject> createTitleLogo(MeshManager meshManager, TextureHandle texture);
}
