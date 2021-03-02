#include "stdafx.h"
#include "..\Include\HomingBulletMove.h"


HomingBulletMove::HomingBulletMove(Desc* _desc)
{
	m_target = _desc->target->GetTransform();

	m_winPos = _desc->winPos;
	m_speed = _desc->speed;
	m_force = _desc->force;
}

void HomingBulletMove::Initialize()
{
	auto player = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER);

	Vector3 playerLook = player->GetTransform()->GetForward();
	Vector3 playerRight = player->GetTransform()->GetRight();
	Vector3 playerUp = player->GetTransform()->GetUp();

	Vector3 winDir = playerRight * m_winPos.x + playerUp * m_winPos.y;
	D3DXVec3Normalize(&winDir, &winDir);

	m_moveDir = playerLook + winDir;
	
	m_rigidbody = GetComponent<Rigidbody>();
	m_rigidbody->SetVelocity(m_moveDir * m_speed);
}

void HomingBulletMove::Update()
{
	m_transform->LookAt(m_target->position, 10.f);
	//m_rigidbody->AddTorque(toTargetDir * m_torque);
	//m_rigidbody->AddForce(m_moveDir * m_force);

	m_rigidbody->AddForceForward(m_force);

}
