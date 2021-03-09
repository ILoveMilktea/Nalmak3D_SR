#include "stdafx.h"
#include "..\Include\HomingBulletMove.h"

#include "Player_Weapon_Homing.h"
#include "PlayerInfoManager.h"
#include "PlayerShooter.h"
#include "ItemManager.h"
#include "Enemy.h"
#include "Enemy_Boss.h"

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

	m_transform->LookAt(dir + m_transform->position, 2.5f);
	m_rigidbody->AddForce(dir * m_force);

	// temp destroy
	m_tempTimer += TimeManager::GetInstance()->GetdeltaTime();
	if (3.f < m_tempTimer)
	{
		DESTROY(m_gameObject);
		m_gameObject = nullptr;
	}
}

void HomingBulletMove::OnTriggerEnter(Collisions & _collision)
{
	int iDmg = ItemManager::GetInstance()->FindItemObject(L"Weapon", L"HomingMissile")->GetItmeInfo().weaponAttak;

	for (auto& obj : _collision)
	{
		
		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_ENEMY)
		{
			obj.GetGameObject()->GetComponent<Enemy>()->Damaged(iDmg);
				
			DESTROY(m_gameObject);
			m_gameObject = nullptr;
		}

		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_BOSS)
		{
			obj.GetGameObject()->GetComponent<Boss>()->Damaged(iDmg);

			DESTROY(m_gameObject);
			m_gameObject = nullptr;

		}

	}
}

void HomingBulletMove::OnTriggerStay(Collisions & _collision)
{
}

void HomingBulletMove::OnTriggerExit(Collisions & _collision)
{
}
