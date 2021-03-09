#include "stdafx.h"
#include "..\Include\Enemy_Evasion_Disappear.h"


Enemy_Evasion_Disappear::Enemy_Evasion_Disappear()
{
}


Enemy_Evasion_Disappear::~Enemy_Evasion_Disappear()
{
}

void Enemy_Evasion_Disappear::Initialize()
{
}

void Enemy_Evasion_Disappear::EnterState()
{
	m_startPos = m_transform->position;
}

void Enemy_Evasion_Disappear::UpdateState()
{
	float inverseRate = 1.f - m_timer;
	float sLerpTimer = 1.f - inverseRate * inverseRate;
	m_transform->position = Nalmak_Math::Lerp(m_startPos, m_destPos, sLerpTimer);

	m_timer += dTime;

	if (m_timer > 1.f)
	{
		DESTROY(m_gameObject);
		return;
	}
}

void Enemy_Evasion_Disappear::ExitState()
{
}
