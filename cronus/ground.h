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
struct TextureHandle;
struct Transform;

namespace factory
{
    std::unique_ptr<GameObject> createGround(MeshManager meshManager, TextureHandle texture, Transform transform);
}
