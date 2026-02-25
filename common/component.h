//-------------------------------------
//
//　コンポーネントの基底 [component.h]
// Author: Fuma Sato
//
//-------------------------------------
#pragma once

class Renderer;
class GameObject;

//---------------------------------
// コンポーネントの基底クラス
//---------------------------------
class Component
{
public:
    Component() : m_owner{} {}
    virtual ~Component() = default;

    virtual bool Awake() { return true; }
    virtual bool Start() { return true; }
    virtual void Update(float deltaTime) {}
    virtual void Draw(const Renderer& renderer) {}
    virtual void Destroy() {}

    void SetOwner(GameObject* owner) { m_owner = owner; }

private:
     GameObject* m_owner;
};
