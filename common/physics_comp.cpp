//--------------------------------------------
//
// 物理コンポーネント [physics_comp.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "physics_comp.h"
#include "physics.h"
#include "object.h"
#include "trans_comp.h"
#include "log.h"

//--------------------------------------------
//
// 物理コンポーネントクラス
//
//--------------------------------------------

//---------------------------
// 初期化
//---------------------------
bool PhysicsComponent::start()
{
    /// 物理に登録する
    auto& owner = getOwner();
    auto trans = owner.getTransform();
    auto transform = trans->get();

    transform *= m_offsetTransform; // オフセットを加算
    m_physicsManager.addRigidBody(getID(), m_collisionShapeType, transform, m_isTrigger, m_rigidBodyType, m_mass, m_collisionGroup, m_collisionMask);
    return true;
}

//---------------------------
// 更新
//---------------------------
void PhysicsComponent::physicsSync()
{
    // 物理をもとに位置を更新する
    auto& owner = getOwner();
    auto trans = owner.getTransform();

    // 物理の結果を取得してTransformに反映 (位置と回転のみ)
    Transform current = trans->get();
    Transform physicsResult = m_physicsManager.getTransform(getID());

    current.position = physicsResult.position;
    current.rotation = physicsResult.rotation;
    current /= m_offsetTransform; // オフセットを減算
    trans->set(current);
}

//---------------------------
// 描画
//---------------------------
void PhysicsComponent::render(Renderer& renderer)
{

}

//---------------------------
// 破棄
//---------------------------
void PhysicsComponent::destroy()
{
    // 物理を破棄
    m_physicsManager.removeRigidBody(getID());
}

//---------------------------
// 物理操作ラッパー
//---------------------------
void PhysicsComponent::addForce(const Vector3& force, bool isImpulse)
{
    m_physicsManager.addForce(getID(), force, isImpulse);
}
void PhysicsComponent::addTorque(const Vector3& torque, bool isImpulse)
{
    m_physicsManager.addTorque(getID(), torque, isImpulse);
}
void PhysicsComponent::setLinearVelocity(const Vector3& velocity)
{
    m_physicsManager.setLinearVelocity(getID(), velocity);
}
void PhysicsComponent::setAngularVelocity(const Vector3& velocity)
{
    m_physicsManager.setAngularVelocity(getID(), velocity);
}
void PhysicsComponent::setTransform(const Transform& transform, bool isResetForces, bool isUpdateMass)
{
    m_physicsManager.setTransform(getID(), transform * m_offsetTransform, isResetForces, isUpdateMass);

    // Transformにも即時反映
    auto trans = getOwner().getTransform();
    trans->set(transform);
}
void PhysicsComponent::setMaterial(float friction, float restitution)
{
    m_physicsManager.setMaterial(getID(), friction, restitution);
}

void PhysicsComponent::setAngularFactor(const Vector3& factor)
{
    m_physicsManager.setAngularFactor(getID(), factor);
}

void PhysicsComponent::setActivationState(bool isActive)
{
    m_physicsManager.setActivationState(getID(), isActive);
}

void PhysicsComponent::setPreventSleep(bool preventSleep)
{
    m_physicsManager.setPreventSleep(getID(), preventSleep);
}

void PhysicsComponent::setDamping(float linearDamping, float angularDamping)
{
    m_physicsManager.setDamping(getID(), linearDamping, angularDamping);
}
