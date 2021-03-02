#include "stdafx.h"
#include "..\Include\HomingBulletMove.h"

#include "Player_Weapon_Homing.h"

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

	// temp destroy
	m_tempTimer = 0.f;
}

void HomingBulletMove::Update()
{


	Vector3 dir = m_target->position - m_transform->position;
	D3DXVec3Normalize(&dir, &dir);

	m_transform->LookAt(dir + m_transform->position, 1.5f);
	m_rigidbody->AddForce(dir * m_force);

	// temp destroy
	m_tempTimer += TimeManager::GetInstance()->GetdeltaTime();
	if (3.f < m_tempTimer)
		DESTROY(m_gameObject);
}
