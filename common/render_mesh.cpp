//--------------------------------------------
//
// Mesh描画用コンポーネント [render_mesh.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "render_mesh.h"
#include "renderer.h"
#include "object.h"
#include "trans_comp.h"
#include "log.h"

//-------------------------------------
// 
// Mesh描画用コンポーネントクラス
// 
//-------------------------------------

//----------------------------
// 描画
//----------------------------
void MeshRenderComponent::render(Renderer& renderer)
{
    // ワールド変換の設定
    Transform transform{};
    auto& owner = getOwner();
    if (owner.Has<TransformComponent>())
    {
        auto comps = owner.Get<TransformComponent>();
        if (comps.size() == 1)
        {
            transform = comps[0]->get();
        }
    }
    else
    {
        transform.identity();
        spdlog::warn("MeshRenderComponent: Owner does not have TransformComponent. Using identity transform.");
    }
    renderer.setTransformWorld(transform.toMatrix());

    // マテリアルとテクスチャの設定
    renderer.setMaterial(m_material);
    renderer.setTexture(m_texture);

    // 描画
    renderer.setRasMode(getRasMode());
    renderer.drawMesh(m_mesh);
    renderer.setRasMode(RasMode::Back);
}
