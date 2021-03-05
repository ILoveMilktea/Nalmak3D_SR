#include "stdafx.h"
#include "..\Include\Player_NearGuideBullet.h"
#include "EnemyManager.h"

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
}

void Player_NearGuideBullet::Update()
{
	// 데드 조건
	if (Nalmak_Math::Distance(m_player->GetTransform()->position, m_transform->position) > 150.f)
	{
		DESTROY(m_gameObject);
	}

	if (!m_bFinish && Nalmak_Math::Distance(m_firstTarget, m_transform->position) > 5.f)
	{
		m_transform->position += m_firstDir * (m_speed * 0.5f) * dTime;
		m_transform->LookAt(m_firstDir + m_transform->position, 1.f);
		
	}
	else
	{
		m_bFinish = true;
	}

	if (!m_bFinish)
		return;

	GameObject * target = EnemyManager::GetInstance()->NearFindEenemy(m_gameObject);
	if (target)
	{
		Vector3 toDistance = target->GetTransform()->position - m_transform->position;
		D3DXVec3Normalize(&toDistance, &toDistance);

		m_transform->position += toDistance * (m_speed)* dTime;
		m_transform->LookAt(toDistance + m_transform->position, 5.5f);
	}
	else
	{
		DESTROY(m_gameObject);
		m_gameObject = nullptr;
	}

}

void Player_NearGuideBullet::Release()
{
}


