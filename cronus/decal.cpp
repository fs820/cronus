//--------------------------------------------
//
// タイトルロゴ [title_rogo.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "decal.h"
#include "object.h"
#include "trans_comp.h"
#include "render_decal.h"
#include "texture.h"
#include "mesh.h"

namespace factory
{
    std::unique_ptr<GameObject> createDecal(MeshManager meshManager, TextureHandle texture, Transform transform, Color color)
    {
        std::unique_ptr<GameObject> decal = std::make_unique<GameObject>(transform);

        MeshHandle mesh = meshManager.box();

        decal->add<DecalRenderComponent>(mesh, texture, color);
        return decal;
    }
}
