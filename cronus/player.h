//--------------------------------------------
//
// プレイヤー [player.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#include <memory>

class GameObject;
class ModelManager;
struct ModelHandle;
class PhysicsManager;
class Renderer;
struct Transform;

namespace factory
{
    std::unique_ptr<GameObject> createPlayer(ModelManager& modelManager, PhysicsManager& physicsManager, Renderer& renderer, ModelHandle model, Transform transform, float offsetModelScale = 1.0f);
}
