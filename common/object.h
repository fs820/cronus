//-------------------------------------
//
//　ゲームオブジェクト [object.h]
// Author: Fuma Sato
//
//-------------------------------------
#pragma once
#include <stdexcept>
#include <memory>
#include <vector>
#include "component.h"

//---------------------------------
// ゲームオブジェクトクラス
//---------------------------------
class GameObject
{
public:
    GameObject() : m_isMarkedForDestroy{} {}
    ~GameObject();

    GameObject(GameObject&&) noexcept = default;
    GameObject& operator=(GameObject&&) noexcept = default;
    GameObject(const GameObject&) = delete;
    GameObject& operator=(const GameObject&) = delete;

    //-----------------------
    // コンポーネントの追加
    //-----------------------
    template<typename T, typename... Args>
        requires std::derived_from<T, Component>
    T* Add(Args&&... args)
    {
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        component->setOwner(this);
        component->awake();

        T* ref = component.get();
        m_components.push_back(std::move(component));
        return ref;
    }

    //-----------------------
    // コンポーネントの取得
    //-----------------------
    template<typename T>
        requires std::derived_from<T, Component>
    bool Has() const
    {
        for (auto& component : m_components)
        {
            if (dynamic_cast<T*>(component.get()) != nullptr)
                return true;
        }
        return false;
    }

    //-----------------------
    // コンポーネントの取得
    //-----------------------
    template<typename T>
        requires std::derived_from<T, Component>
    std::vector<T*> Get()
    {
        std::vector<T*> components;
        for (auto& component : m_components)
        {
            auto pComp = dynamic_cast<T*>(component.get());
            if (pComp != nullptr)
                components.push_back(pComp);
        }
        return components;
    }

    bool Start();
    void Update(float deltaTime);
    void Destroy();
    void markForDestroy() { m_isMarkedForDestroy = true; }
    bool isMarkedForDestroy() const { return m_isMarkedForDestroy; }

private:
    std::vector<std::unique_ptr<Component>> m_components; // コンポーネント
    bool m_isMarkedForDestroy;                            // 破棄予定フラグ
};
