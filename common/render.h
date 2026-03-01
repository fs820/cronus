//--------------------------------------------
//
// 描画用コンポーネント [render.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#include "component.h"
#include "graphics_types.h"

//-------------------------------------
// 描画用コンポーネントクラス [抽象]
//-------------------------------------
class RenderComponent : public Component
{
public:
    RenderComponent(const RenderQueue& renderQueue, const RasMode& rasMode);
    virtual ~RenderComponent();

    virtual void render(Renderer& renderer) override = 0;

    void setRenderQueue(const RenderQueue& renderQueue) { m_renderQueue = renderQueue; }
    RenderQueue getRenderQueue() const { return m_renderQueue; }
    void setRasMode(RasMode mode) { m_rasMode = mode; }
    RasMode getRasMode() { return m_rasMode; }

private:
    RenderQueue m_renderQueue;
    RasMode m_rasMode;
};
