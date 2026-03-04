//--------------------------------------------
//
// 地面 [ground.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#include <memory>

class GameObject;
class MeshManager;
class TextureManager;
struct TextureHandle;
struct Transform;

namespace factory
{
    std::unique_ptr<GameObject> createGround(MeshManager& meshManager, const TextureManager& textureManager, TextureHandle texture, Transform transform, float tileMag = 100.0f);
}
