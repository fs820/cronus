//--------------------------------------------
//
// Modelコンポーネント [model_comp.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "model_comp.h"
#include "model.h"

void ModelComponent::set(Model* pModel) { m_pModel.reset(pModel); }
Model* ModelComponent::get() const { return m_pModel.get(); }
