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
    std::unique_ptr<GameObject> createSky(MeshManager& meshManager, const TextureManager& textureManager, TextureHandle texture, Transform transform)
    {
        std::unique_ptr<GameObject> sky = std::make_unique<GameObject>();

        sky->Add<TransformComponent>(transform);

        // テクスチャの登録
        int width{ 100 }, height{ 100 };
        textureManager.getTextureSize(texture, width, height);

        // 球のメッシュ
        float texAspect = float(height) / float(width);
        MeshHandle mesh = meshManager.sphere(texAspect * 4.0f, 1.0f, 64u, 64u, true, true);
        Material material{};

        sky->Add<MeshRenderComponent>(RenderQueueMask::Sky, RasMode::Back, mesh, material, texture);
        return sky;
    }
}
