//--------------------------------------------
//
// 地面 [worldend.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "worldend.h"
#include "object.h"
#include "trans_comp.h"
#include "render_mesh.h"
#include "mesh.h"
#include "texture.h"
#include "mymath.h"

namespace factory
{
    std::unique_ptr<GameObject> createWorldEnd(MeshManager& meshManager, const TextureManager& textureManager, TextureHandle texture, Transform transform)
    {
        std::unique_ptr<GameObject> worldEnd = std::make_unique<GameObject>(transform);

        // テクスチャの登録
        int width{ 100 }, height{ 100 };
        textureManager.getTextureSize(texture, width, height);

        // 柱のメッシュ
        float texAspect = float(height) / float(width);
        float widthMag = (((transform.scale.x + transform.scale.z) * 0.5f) * math::PI) / transform.scale.y;
        MeshHandle mesh = meshManager.cylinder(texAspect * widthMag, 1.0f, 64u, true);
        Material material{};

        worldEnd->add<MeshRenderComponent>(RenderQueueMask::Geometry, RasMode::Back, mesh, material, texture);
        return worldEnd;
    }
}
