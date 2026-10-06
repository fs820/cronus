//--------------------------------------------
//
// プレイヤーの操作ロジック [player_controller.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "player_controller.h"
#include "input.h"
#include "physics_comp.h"
#include "object.h"

//---------------------------
// プレイヤーの操作ロジック
//---------------------------

//---------------------------
// 初期化
//---------------------------
bool PlayerControllerComponent::start()
{
    // 自分のGameObjectのPhysicsComponentを保持
    m_physics = getOwner().get<PhysicsComponent>()[0];

    m_physics->setAngularFactor(Vector3::Zero()); // 回転を無効化
    m_physics->setPreventSleep(true);             // 物理をスリープさせない

    return m_physics != nullptr;
}

//---------------------------
// 更新
//---------------------------
void PlayerControllerComponent::update(float deltaTime)
{
    if (m_physics == nullptr) return;

    // ジャンプ
    if (m_input.isActionPressed(ActionCode::Jump))
    {
        m_physics->addForce(Vector3(0.0f, 5.0f, 0.0f), true);
    }

    // 移動
    Vector2 moveAxis = m_input.getAxis2D(ActionCode::Move);
    if (moveAxis.length() > 0.0f)
    {
        m_physics->addForce(Vector3(moveAxis.x, 0.0f, -moveAxis.y) * deltaTime * 1000.0f);
    }
}
