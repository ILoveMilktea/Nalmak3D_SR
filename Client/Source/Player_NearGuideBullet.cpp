#include "stdafx.h"
#include "..\Include\Player_NearGuideBullet.h"


Player_NearGuideBullet::Player_NearGuideBullet(Desc * _desc)
{
	m_firstTarget = _desc->firstTarget;
	m_speed = _desc->speed;
}


Player_NearGuideBullet::~Player_NearGuideBullet()
{
}

void Player_NearGuideBullet::Initialize()
{
	m_firstDir = m_firstTarget - m_transform->position;
	
	D3DXVec3Normalize(&m_firstDir, &m_firstDir);
}

void Player_NearGuideBullet::Update()
{

	if (Nalmak_Math::Distance(m_firstTarget, m_transform->position) > 0.2f)
	{
		m_transform->position += m_firstDir * m_speed * dTime;
	}
}
