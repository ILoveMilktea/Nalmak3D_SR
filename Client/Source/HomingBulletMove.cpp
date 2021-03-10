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

HomingBulletMove::~HomingBulletMove()
{
	if (m_finalPos)
	{
		delete m_finalPos;
		m_finalPos = nullptr;
	}
}

void HomingBulletMove::Initialize()
{
	m_player = PlayerInfoManager::GetInstance()->GetPlayer();

	Vector3 playerLook = m_player->GetTransform()->GetForward();
	Vector3 playerRight = m_player->GetTransform()->GetRight();
	Vector3 playerUp = m_player->GetTransform()->GetUp();

	Vector3 winDir = playerRight * m_winPos.x + playerUp * m_winPos.y;
	D3DXVec3Normalize(&winDir, &winDir);

	m_moveDir = playerLook + winDir;
	

	//m_rigidbody = GetComponent<Rigidbody>();
	//m_rigidbody->SetVelocity(m_moveDir * m_speed);

	// temp destroy
	m_tempTimer = 0.f;

	if(m_target)
		m_finalPos = new Vector3(m_target->position);
	else
		ZeroMemory(m_finalPos, sizeof(Vector3));
	
}

void HomingBulletMove::Update()
{
	
	if (m_finalPos)
	{
		if (*m_finalPos == Vector3(0,0,0))
			return;

		if (Nalmak_Math::Distance(*m_finalPos, m_transform->position) > 5.f)
		{
			Vector3 dir = *m_finalPos - m_transform->position;
			D3DXVec3Normalize(&dir, &dir);
			m_moveDir = Nalmak_Math::Lerp(m_moveDir, m_player->GetTransform()->GetForward(), dTime);
			m_transform->position += ((dir + m_moveDir) * m_speed * dTime);
			m_transform->LookAt(dir + m_transform->position, 2.5f);

		}
		else if (Nalmak_Math::Distance(*m_finalPos, m_transform->position) <= 5.f)
		{
			delete m_finalPos;
			m_finalPos = nullptr;
		}
	}
	else
	{
		m_transform->position += m_transform->GetForward() * m_speed * dTime;
		//m_transform->LookAt(m_transform->GetForward() , 5.5f);

		m_tempTimer += TimeManager::GetInstance()->GetdeltaTime();
		if (3.f < m_tempTimer)
		{
			DESTROY(m_gameObject);
			m_gameObject = nullptr;
		}
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
