//--------------------------------------------
//
// タイトルロゴ [title_rogo.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "title_rogo.h"
#include "object.h"
#include "trans_comp.h"
#include "render_mesh.h"
#include "mesh.h"
#include "texture.h"

namespace factory
{
    std::unique_ptr<GameObject> createTitleLogo(MeshManager meshManager, TextureHandle texture, Transform transform)
    {
        std::unique_ptr<GameObject> logo = std::make_unique<GameObject>(transform);

        MeshHandle mesh = meshManager.sprite(); // スプライト
        Material material{};                    // デフォルトf

        logo->add<MeshRenderComponent>(RenderQueueMask::UI, RasMode::Back, mesh, material, texture);
        return logo;
    }
}
