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

namespace factory
{
    std::unique_ptr<GameObject> createBoard(MeshManager& meshManager, TextureHandle texture, Transform transform)
    {
        std::unique_ptr<GameObject> worldEnd = std::make_unique<GameObject>();

        worldEnd->Add<TransformComponent>(transform);

        // 板のメッシュ
        MeshHandle mesh = meshManager.quad();
        Material material{};
        material.Emissive = { 0.2f,0.2f,0.2f,0.5f };

        worldEnd->Add<MeshRenderComponent>(RenderQueueMask::Transparent | RenderQueueMask::Outline, RasMode::Back, mesh, material, texture);
        return worldEnd;
    }
}
