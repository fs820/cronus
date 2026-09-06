//--------------------------------------------
//
// 地面 [ground.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "ground.h"
#include "object.h"
#include "trans_comp.h"
#include "render_mesh.h"
#include "physics_comp.h"
#include "mesh.h"
#include "texture.h"

namespace factory
{
    std::unique_ptr<GameObject> createGround(MeshManager& meshManager, const TextureManager& textureManager, PhysicsManager& physicsManager, TextureHandle texture, Transform transform, float tileMag)
    {
        std::unique_ptr<GameObject> ground = std::make_unique<GameObject>(transform);

        // テクスチャの登録
        int width{ 100 }, height{ 100 };
        textureManager.getTextureSize(texture, width, height);

        // メッシュ
        MeshHandle mesh = meshManager.quad((transform.scale.x / width) * tileMag, (transform.scale.y / height) * tileMag);

        Material material{};
        material.pixelShaderType = PixelShaderType::Toon;

        ground->add<MeshRenderComponent>(RenderQueueMask::Geometry, RasMode::Back, mesh, material, texture);

        // 物理コンポーネントの追加
        ground->add<PhysicsComponent>(physicsManager,
            CollisionShapeType::Plane, RigidBodyType::Static,
            0.0f, false,
            CollisionGroup::Environment, CollisionGroup::Player | CollisionGroup::Enemy);

        return ground;
    }
}
