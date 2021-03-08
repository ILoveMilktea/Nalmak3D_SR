#include "stdafx.h"
#include "..\Include\Player_NearGuideBullet.h"
#include "ItemManager.h"

#include "PlayerItem.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "Enemy_Boss.h"

#include "PlayerInfoManager.h"
#include "EnemyDetector.h"
Player_NearGuideBullet::Player_NearGuideBullet(Desc * _desc)
{
	m_firstTarget = _desc->firstTarget;
	m_speed = _desc->speed;
}


Player_NearGuideBullet::~Player_NearGuideBullet()
{
	m_gameObject = nullptr;
}

void Player_NearGuideBullet::Initialize()
{
	m_firstDir = m_firstTarget - m_transform->position;
	D3DXVec3Normalize(&m_firstDir, &m_firstDir);
	m_player = PlayerInfoManager::GetInstance()->GetPlayer();
	m_enemyDetector = Core::GetInstance()->FindObjectByName(OBJECT_TAG_UI, L"detector")->GetComponent<EnemyDetector>();
	m_target = m_enemyDetector->GetLockOnTarget();
	m_finalTargetPos = m_target->GetTransform()->position;
}

void Player_NearGuideBullet::Update()
{
	// 데드 조건
	if (Nalmak_Math::Distance(m_player->GetTransform()->position, m_transform->position) > 600.f)
	{
		DESTROY(m_gameObject);
		m_gameObject = nullptr;
	}

	if (!m_bFinish && Nalmak_Math::Distance(m_firstTarget, m_transform->position) > 2.f)
	{
		m_transform->position = Nalmak_Math::Lerp(m_transform->position, m_firstTarget, dTime * 5.f);
		m_transform->LookAt(m_firstDir + m_transform->position, 1.f);

	}
	else
	{
		m_bFinish = true;
	}

	if (!m_bFinish)
		return;

	
	
	if (Nalmak_Math::Distance(m_finalTargetPos, m_transform->position) >= 1.f)
	{
		Vector3 toDistance = m_finalTargetPos - m_transform->position;
		D3DXVec3Normalize(&toDistance, &toDistance);
		m_transform->position = Nalmak_Math::Lerp(m_transform->position, m_finalTargetPos, dTime * 5.f);
		m_transform->LookAt(toDistance + m_transform->position, 5.5f);
	}
	else
	{
		m_transform->position += m_transform->GetForward() * 45 * dTime;
		//m_transform->SetRotation(0, 0, 0);
	}

}

void Player_NearGuideBullet::Release()
{
}

void Player_NearGuideBullet::OnTriggerEnter(Collisions & _collision)
{

	m_dmg = ItemManager::GetInstance()->FindItemObject(L"Weapon", L"ClusterMissile")->GetItmeInfo().weaponAttak;

	for (auto& obj : _collision)
	{
		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_ENEMY)
		{
			obj.GetGameObject()->GetComponent<Enemy>()->Damaged(m_dmg);

			DESTROY(m_gameObject);
			m_gameObject = nullptr;
		}

		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_BOSS)
		{
			obj.GetGameObject()->GetComponent<Boss>()->Damaged(m_dmg);
			DESTROY(m_gameObject);
			m_gameObject = nullptr;

		}
	}
}

void Player_NearGuideBullet::OnTriggerStay(Collisions & _collision)
{
}

void Player_NearGuideBullet::OnTriggerExit(Collisions & _collision)
{
}


