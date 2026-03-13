//--------------------------------------------
//
// ボード [board.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#include <memory>

class GameObject;
class MeshManager;
class Camera;
struct TextureHandle;
struct Transform;

namespace factory
{
    std::unique_ptr<GameObject> createBoard(MeshManager& meshManager, const Camera& camera, TextureHandle texture, Transform transform);
}
