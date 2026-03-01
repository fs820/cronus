//-------------------------------------
//
//　ゲームオブジェクト [object.h]
// Author: Fuma Sato
//
//-------------------------------------
#pragma once
#include <unordered_map>
#include <typeindex>
#include <stdexcept>
#include <memory>
#include "component.h"

//---------------------------------
// ゲームオブジェクトクラス
//---------------------------------
class GameObject
{
public:
    GameObject() : m_isMarkedForDestroy{} {}
    ~GameObject();

    //-----------------------
    // コンポーネントの追加
    //-----------------------
    template<typename T, typename... Args>
        requires std::derived_from<T, Component>
    T& Add(Args&&... args)
    {
        auto type = std::type_index(typeid(T));
        if (m_components.contains(type))
        {
            throw std::runtime_error("Component already exists");
        }
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        component->setOwner(this);
        component->awake();

        T& ref = *component;
        m_components[type] = std::move(component);
        return ref;
    }

    //-----------------------
    // コンポーネントの取得
    //-----------------------
    template<typename T>
        requires std::derived_from<T, Component>
    bool Has() const
    {
        for (auto& [type, comp] : m_components)
        {
            if (dynamic_cast<T*>(comp.get()) != nullptr)
                return true;
        }
        return false;
    }

    //-----------------------
    // コンポーネントの取得
    //-----------------------
    template<typename T>
        requires std::derived_from<T, Component>
    T& Get()
    {
        auto type = std::type_index(typeid(T));
        if (!m_components.contains(type))
        {
            throw std::runtime_error("Component does not exist");
        }
        return *static_cast<T*>(m_components[type].get());
    }

    bool Start();
    void Update(float deltaTime);
    void Render(Renderer& renderer);
    void Destroy();
    void markForDestroy() { m_isMarkedForDestroy = true; }
    bool isMarkedForDestroy() const { return m_isMarkedForDestroy; }

private:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components; // コンポーネントのマップ
    bool m_isMarkedForDestroy;                                                    // 破棄予定フラグ
};
