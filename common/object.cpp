//-------------------------------------
//
//　ゲームオブジェクト [object.cpp]
// Author: Fuma Sato
//
//-------------------------------------
#include "object.h"
#include "component.h"

//---------------------------------
// ゲームオブジェクトクラス
//---------------------------------
GameObject::~GameObject() { Destroy(); }

//-----------------------
// コンポーネントの開始
//-----------------------
bool GameObject::Start()
{
    for (auto& component : m_components)
    {
        if (!component->start())
        {
            return false;
        }
    }
    return true;
}

//-----------------------
// コンポーネントの更新
//-----------------------
void GameObject::Update(float deltaTime)
{
    for (auto& component : m_components)
    {
        component->update(deltaTime);
    }
}

//-----------------------
// コンポーネントの破棄
//-----------------------
void GameObject::Destroy()
{
    for (auto& component : m_components)
    {
        component->destroy();
    }
    m_components.clear();
}
