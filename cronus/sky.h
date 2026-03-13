//--------------------------------------------
//
// 空 [sky.h]
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
    std::unique_ptr<GameObject> createSky(MeshManager& meshManager, const TextureManager& textureManager, TextureHandle texture, Transform transform);
}
