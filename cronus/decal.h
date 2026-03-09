//--------------------------------------------
//
// デカール[decal.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#include <memory>
#include "graphics_types.h"

class GameObject;
class MeshManager;
struct TextureHandle;
struct Transform;

namespace factory
{
    std::unique_ptr<GameObject> createDecal(MeshManager meshManager, TextureHandle texture, Transform transform, Color color = Color::White());
}
