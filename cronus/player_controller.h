//--------------------------------------------
//
// プレイヤーの操作ロジック [player_controller.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#include "component.h"

class Input;
class PhysicsComponent;

//----------------------------
// プレイヤーの操作ロジック
//----------------------------
class PlayerControllerComponent : public Component
{
public:
    PlayerControllerComponent(Input& input) : m_input(input), m_physics(nullptr) {}
    virtual ~PlayerControllerComponent() override = default;

    bool start() override;
    void update(float deltaTime) override;

private:
    Input& m_input;
    PhysicsComponent* m_physics;
};
