//--------------------------------------------
//
// Lightコンポーネント [light_comp.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#include "component.h"
#include "graphics_types.h"

//-------------------------------------
// Lightコンポーネントクラス
//-------------------------------------
class LightComponent : public Component
{
public:
    LightComponent(const LightData& renderQueue, bool isShadowCast = false, const Vector3& shadowEye = {}, const Vector3& shadowTarget = {}, const Vector3& shadowUp = {}) : m_data(renderQueue), m_isShadowCast(isShadowCast),m_shadowEye(shadowEye),m_shadowTarget(shadowTarget),m_shadowUp(shadowUp) {}
    virtual ~LightComponent() = default;

    void set(const LightData& light) { m_data = light; }
    LightData get() const { return m_data; }

    void setShadowInfo(bool isShadowCast, const Vector3& shadowEye = {}, const Vector3& shadowTarget = {}, const Vector3& shadowUp = {})
    {
        m_isShadowCast = isShadowCast; m_shadowEye = shadowEye; m_shadowTarget = shadowTarget; m_shadowUp = shadowUp;
    }
    bool getShadowInfo(Vector3* shadowEye = nullptr, Vector3* shadowTarget = nullptr, Vector3* shadowUp = nullptr)
    {
        shadowEye = &m_shadowEye; shadowTarget = &m_shadowTarget; shadowUp = &m_shadowUp;
        return m_isShadowCast;
    }

private:
    LightData m_data;       // ライト
    bool m_isShadowCast;    // 影を落とすかどうか

    // 影を落とす場合
    Vector3 m_shadowEye;    // 視点
    Vector3 m_shadowTarget; // 注視点
    Vector3 m_shadowUp;     // 上
};
