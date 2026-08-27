#pragma once
class Component;

//-----------------------------------------------
// コンポーネントを登録・解除のインターフェース
//-----------------------------------------------
class IComponentRegistry
{
public:
    virtual ~IComponentRegistry() = default;
    virtual void registerComponent(Component* comp) = 0;
    virtual void unregisterComponent(Component* comp) = 0;
};
