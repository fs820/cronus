//--------------------------------------------
//
// タイトルロゴ [title_rogo.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "ground.h"
#include "object.h"
#include "trans_comp.h"
#include "render_mesh.h"
#include "mesh.h"
#include "texture.h"

namespace factory
{
    std::unique_ptr<GameObject> createGround(MeshManager meshManager, TextureHandle texture, Transform transform)
    {
        std::unique_ptr<GameObject> ground = std::make_unique<GameObject>();

        auto pTrans = ground->Add<TransformComponent>(transform);

        MeshHandle mesh = meshManager.quad();
        Material material{};
        material.pixelShaderType = PixelShaderType::Toon;

        ground->Add<MeshRenderComponent>(RenderQueue::Geometry, RasMode::Back, mesh, material, texture);
        return ground;
    }
}
