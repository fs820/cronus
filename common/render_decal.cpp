//--------------------------------------------
//
// Decal描画用コンポーネント [render_decal.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "render_decal.h"
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
void DecalRenderComponent::render(Renderer& renderer)
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

    // テクスチャの設定
    renderer.setTexture(m_texture);

    // 描画
    renderer.drawDecal(transform.toMatrix(), m_mesh, m_color);
}
