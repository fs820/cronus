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
#include "gui.h"

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

#ifdef _DEBUG
    // デバッグ用に位置を表示
    if (ImGui::Begin("Player Controller"))
    {
        ImGui::Text(std::format("Position: ({:.2f}, {:.2f}, {:.2f})", getOwner().getTransform()->get().position.x, getOwner().getTransform()->get().position.y, getOwner().getTransform()->get().position.z).c_str());
        ImGui::End();
    }
#endif // _DEBUG

    // ジャンプ
    if (m_input.isActionPressed(ActionCode::Jump))
    {
        m_physics->addForce(Vector3(0.0f, 5.0f, 0.0f), true);
    }

    // 移動
    Vector2 moveAxis = m_input.getAxis2D(ActionCode::Move);

#ifdef _DEBUG
    // デバッグ用に移動軸を表示
    if (ImGui::Begin("Player Controller"))
    {
        ImGui::Text(std::format("moveAxis: ({:.2f}, {:.2f})", moveAxis.x, moveAxis.y).c_str());
        ImGui::End();
    }
#endif // _DEBUG

    // 移動軸がある場合、回転と移動を行う
    if (moveAxis.length() > 0.0f)
    {
        auto ownerTransform = getOwner().getTransform()->get();
        auto qt = Quaternion::Slerp(ownerTransform.rotation, Quaternion::RotationYawPitchRoll(std::atan2f(-moveAxis.x, moveAxis.y), 0.0f, 0.0f), deltaTime * 10.0f);
        m_physics->setTransform(Transform(ownerTransform.position, qt, ownerTransform.scale), false, false);

#ifdef _DEBUG
        // デバッグ用にクオータニオンを表示
        if (ImGui::Begin("Player Controller"))
        {
            ImGui::Text(std::format("qt: ({:.2f}, {:.2f}), ({:.2f}, {:.2f})", qt.x, qt.y, qt.z, qt.w).c_str());
            ImGui::End();
        }
#endif // _DEBUG

        auto moveVec = qt.rotate({ 0,0,-1 });

#ifdef _DEBUG
        // デバッグ用に移動ベクトルを表示
        if (ImGui::Begin("Player Controller"))
        {
            ImGui::Text(std::format("moveVec: ({:.2f}, {:.2f}, {:.2f})", moveVec.x, moveVec.y, moveVec.z).c_str());
            ImGui::End();
        }
#endif // _DEBUG

        m_physics->addForce(moveVec * deltaTime * 1000.0f);
    }
}
