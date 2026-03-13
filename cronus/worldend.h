//--------------------------------------------
//
// 果て [worldend.h]
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
    std::unique_ptr<GameObject> createWorldEnd(MeshManager& meshManager, const TextureManager& textureManager, TextureHandle texture, Transform transform);
}
