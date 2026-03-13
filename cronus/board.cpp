//--------------------------------------------
//
// ボード [board.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "board.h"
#include "object.h"
#include "trans_comp.h"
#include "render_mesh.h"
#include "mesh.h"
#include "texture.h"
#include "mymath.h"
#include "billboard_comp.h"

namespace factory
{
    std::unique_ptr<GameObject> createBoard(MeshManager& meshManager, const Camera& camera, TextureHandle texture, Transform transform)
    {
        std::unique_ptr<GameObject> worldEnd = std::make_unique<GameObject>();

        worldEnd->Add<TransformComponent>(transform);

        worldEnd->Add<BillboardComponent>(camera, false, true);

        // 板のメッシュ
        MeshHandle mesh = meshManager.quad();
        Material material{};
        material.Emissive = { 2.0f,2.0f,2.0f,1.0f };
        material.Specular = Color::White();

        worldEnd->Add<MeshRenderComponent>(RenderQueueMask::Transparent, RasMode::None, mesh, material, texture);
        return worldEnd;
    }
}
