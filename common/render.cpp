//--------------------------------------------
//
// 描画用コンポーネント [render.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#include "render.h"
#include "renderer.h"

//----------------------------
// 
// 描画用コンポーネントクラス
// 
//----------------------------
RenderComponent::RenderComponent(const RenderQueue& renderQueue) : m_renderQueue(renderQueue) {}
RenderComponent::~RenderComponent() = default;

RenderQueue RenderComponent::GetRenderQueue() const { return m_renderQueue; }
