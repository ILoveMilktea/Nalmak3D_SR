#include "stdafx.h"
#include "..\Include\MidBoss_Appear.h"

#include "MidBoss_Define.h"
#include "Enemy_MidBoss.h"

MidBoss_Appear::MidBoss_Appear()
{
}


MidBoss_Appear::~MidBoss_Appear()
{
}

void MidBoss_Appear::Initialize()
{
}

void MidBoss_Appear::EnterState()
{
	SetInteger(_g_patternIndex, 0);

	m_startPosition = m_transform->position;
	m_centerPosition = _MIDBOSS_CENTERPOS;

	m_lerpTimer = 0.f;
	m_lerpDuration = 8.f;
}

void MidBoss_Appear::UpdateState()
{
	float inverseRate = 1.f - m_lerpTimer / m_lerpDuration;
	float sLerpTimer = 1.f - inverseRate * inverseRate;
	m_transform->position = Nalmak_Math::Lerp(m_startPosition, m_centerPosition, sLerpTimer);

	m_lerpTimer += dTime;

	if (m_lerpTimer >= m_lerpDuration)
	{
		m_transform->position = m_centerPosition;
		SetState(_sn_idle);
		return;
	}

}

void MidBoss_Appear::ExitState()
{
}
