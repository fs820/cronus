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
struct TextureHandle;
struct Transform;

namespace factory
{
    std::unique_ptr<GameObject> createBoard(MeshManager& meshManager, TextureHandle texture, Transform transform);
}
