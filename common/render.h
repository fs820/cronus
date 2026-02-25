//--------------------------------------------
//
// 描画用コンポーネント [render.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#include "component.h"

enum class RenderQueue : unsigned char;

//-------------------------------------
// 描画用コンポーネントクラス [抽象]
//-------------------------------------
class RenderComponent : public Component
{
public:
    RenderComponent(const RenderQueue& renderQueue);
    virtual ~RenderComponent();

    virtual void Draw(const Renderer& renderer) override = 0;

    void SetRenderQueue(const RenderQueue& renderQueue) { m_renderQueue = renderQueue; }
    RenderQueue GetRenderQueue() const;

private:
    RenderQueue m_renderQueue;
};
