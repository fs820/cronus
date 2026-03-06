//--------------------------------------------
//
// Modelコンポーネント [model_comp.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "model_comp.h"
#include "model.h"
#include "object.h"
#include "trans_comp.h"
#include "log.h"

//--------------------------------------------
//
// Modelコンポーネントクラス
//
//--------------------------------------------

//---------------------------
// 更新
//---------------------------
void ModelComponent::update(float deltaTime)
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

    m_pModel->update(deltaTime, transform.toMatrix());
}

void ModelComponent::set(Model* pModel) { m_pModel.reset(pModel); }
Model* ModelComponent::get() const { return m_pModel.get(); }
