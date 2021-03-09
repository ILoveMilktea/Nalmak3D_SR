#include "stdafx.h"
#include "..\Include\Enemy_Evasion_Appear.h"


Enemy_Evasion_Appear::Enemy_Evasion_Appear()
{
}


Enemy_Evasion_Appear::~Enemy_Evasion_Appear()
{
}

void Enemy_Evasion_Appear::Initialize()
{
	
}

void Enemy_Evasion_Appear::EnterState()
{

}

void Enemy_Evasion_Appear::UpdateState()
{
	float inverseRate = 1.f - m_timer;
	float sLerpTimer = 1.f - inverseRate * inverseRate;
	m_transform->position = Nalmak_Math::Lerp(m_startPos, m_destPos, sLerpTimer);

	m_timer += dTime;
	
	if (m_timer > 1.f)
	{
		SetState(m_nextState);
		return;
	}
}

void Enemy_Evasion_Appear::ExitState()
{
	m_transform->position = m_destPos;
}
