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

    virtual bool awake() { return true; }
    virtual bool start() { return true; }
    virtual void update(float deltaTime) {}
    virtual void render(Renderer& renderer) {}
    virtual void destroy() {}

    void setOwner(GameObject* owner) { m_owner = owner; }

protected:
        GameObject& getOwner() { return *m_owner; }
        const GameObject& getOwner() const { return *m_owner; }

private:
     GameObject* m_owner;
};
