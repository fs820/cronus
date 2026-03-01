//--------------------------------------------
//
// Mesh描画用コンポーネント [render_mesh.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#include "render.h"

//-------------------------------------
// Mesh描画用コンポーネントクラス
//-------------------------------------
class MeshRenderComponent : public RenderComponent
{
public:
    MeshRenderComponent(const RenderQueue& renderQueue, RasMode mode, MeshHandle mesh, Material material, TextureHandle texture) : RenderComponent(renderQueue, mode), m_mesh(mesh), m_material(material), m_texture(texture) {}
    ~MeshRenderComponent() = default;

    void render(Renderer& renderer) override;

    void SetMeshHandle(const MeshHandle& mesh) { m_mesh = mesh; }
    void SetMaterial(const Material& material) { m_material = material; }
    void SetTextureHandle(const TextureHandle& texture) { m_texture = texture; }

private:
    MeshHandle m_mesh;       // 描画するメッシュのハンドル
    Material m_material;     // 描画に使用するマテリアル
    TextureHandle m_texture; // 描画に使用するテクスチャ
};
