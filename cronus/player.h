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
class Input;
class Renderer;
struct Transform;

namespace factory
{
    std::unique_ptr<GameObject> createPlayer(ModelManager& modelManager, PhysicsManager& physicsManager, Renderer& renderer, Input& input, ModelHandle model, Transform transform, float offsetModelScale = 1.0f);
}
