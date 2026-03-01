//--------------------------------------------
//
// Cameraコンポーネント [camera_comp.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#include "component.h"
#include "camera.h"

//-------------------------------------
// Cameraコンポーネントクラス
//-------------------------------------
class CameraComponent : public Component
{
public:
    CameraComponent(const Camera& renderQueue) : m_camera(renderQueue) {}
    virtual ~CameraComponent() = default;

    void set(const Camera& camera) { m_camera = camera; }
    Camera get() const { return m_camera; }

private:
    Camera m_camera; // オブジェクトの位置、回転、スケールを表すTransform
};
