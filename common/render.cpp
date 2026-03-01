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
RenderComponent::RenderComponent(const RenderQueue& renderQueue, const RasMode& rasMode) : m_renderQueue(renderQueue), m_rasMode(rasMode){}
RenderComponent::~RenderComponent() = default;
